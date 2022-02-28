/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_cpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:44:53 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/15 14:17:19 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(char **env)
{
	int		i;
	char	**env_cpy;

	env_cpy = (char **)malloc(sizeof(char *) * (ft_tabsize(env) + 2));
	if (!env_cpy)
		exit(EXIT_FAILURE);
	i = -1;
	while (env[++i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			exit(EXIT_FAILURE);
	}
	if (find_var_in_env("OLDPWD", env) == -1)
	{
		env_cpy[i] = ft_strdup("OLDPWD");
		if (!env_cpy[i])
			exit(EXIT_FAILURE);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

long	get_lvl_shlvl(char ***env)
{
	int		i;
	long	lvl;
	char	*temp;

	i = find_var_in_env("SHLVL", *env);
	lvl = 1;
	if (i == -1)
		create_new_var_env("SHLVL=1", env);
	else
	{
		temp = ft_strdup((*env)[i]);
		temp = ft_strtrim(temp, "SHLVL=");
		lvl = ft_atoi(temp);
		if (temp && check_str_digit(temp) && lvl > 0)
			lvl = 1;
		else if (lvl > 0)
			lvl++;
		free(temp);
	}
	return (lvl);
}

void	update_shlvl(char ***env)
{
	int		i;
	long	lvl;
	char	*new_lvl;

	i = find_var_in_env("SHLVL", *env);
	lvl = get_lvl_shlvl(env);
	if (lvl > INT_MAX || lvl < 0)
		lvl = 0;
	if (1000 < lvl && lvl <= INT_MAX)
	{
		write(1, "minishell: warning: shell level (", 33);
		write(1, ft_itoa(lvl), ft_strlen(ft_itoa(lvl)));
		write(1, ") too high, resetting to 1\n", 27);
		lvl = 1;
	}
	i = find_var_in_env("SHLVL", *env);
	new_lvl = ft_itoa(lvl);
	free((*env)[i]);
	(*env)[i] = NULL;
	(*env)[i] = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	new_lvl = NULL;
}
