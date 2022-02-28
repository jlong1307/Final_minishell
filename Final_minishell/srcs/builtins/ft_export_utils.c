/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:23:40 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/18 16:24:15 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_to_find(char *arg)
{
	char	*to_find;
	int		i;
	int		j;

	i = 0;
	j = 0;
	to_find = (char *)malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!to_find)
		exit(EXIT_FAILURE);
	while (arg[j] && arg[j] != '=')
	{
		if (arg[i] == '+')
			j++;
		else
			to_find[i++] = arg[j++];
	}
	to_find[i] = '\0';
	return (to_find);
}

int	find_var_in_env(char *arg, char **env)
{
	char	*to_find;
	int		i;
	int		j;

	to_find = get_to_find(arg);
	i = -1;
	j = 0;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], to_find, j) && ((int)ft_strlen(to_find) == j))
		{
			free(to_find);
			to_find = NULL;
			return (i);
		}
	}
	free(to_find);
	to_find = NULL;
	return (-1);
}

int	check_if_already_in_env(char *arg, char ***env)
{
	int	i;

	i = -1;
	while (arg && (*env)[++i])
	{
		if (!ft_strncmp(arg, (*env)[i], ft_strlen(arg) + 1))
			return (1);
	}
	return (0);
}

char	*ft_to_add(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	i = 0;
	while (str[i] != '=')
		i++;
	count = (int)ft_strlen(str) - i - 1;
	res = (char *)malloc(sizeof(char) * (count + 1));
	if (!res)
		exit(EXIT_FAILURE);
	j = 0;
	while (str[++i])
		res[j++] = str[i];
	res[j] = '\0';
	return (res);
}

void	modify_var_in_env(char *arg, char ***env)
{
	char	*temp;
	char	*to_add;
	int		i;

	i = find_var_in_env(arg, *env);
	if (ft_strchr_modified(arg, '+'))
	{
		to_add = ft_to_add(arg);
		if (ft_strchr_modified((*env)[i], '='))
			temp = ft_strjoin((*env)[i], to_add);
		else
		{
			temp = ft_strjoin((*env)[i], "=");
			temp = ft_strjoin_free(temp, to_add);
		}
		free(to_add);
		to_add = NULL;
	}
	else
		temp = ft_strdup(arg);
	free((*env)[i]);
	(*env)[i] = NULL;
	(*env)[i] = temp;
}
