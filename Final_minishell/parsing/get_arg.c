/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:03 by jlong             #+#    #+#             */
/*   Updated: 2022/01/24 13:30:51 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	check_is_opt_echo(char *line)
{
	int	i;

	i = 0;
	if (line && line[i] == '-' && line[i + 1] != '\0')
	{
		i++;
		while (line[i] != '\0')
		{
			if (line[i] != 'n')
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	check_is_opt(char *line)
{
	int	i;

	i = 0;
	if (line && line[i] == '-' && line[i + 1] != '\0')
	{
		i++;
		while (line[i] != '\0')
		{
			if (line[i] == ' ')
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

char	**return_arg(char *line, char **env, int n, int index)
{
	char	**tmp;
	int		m;
	char	**tab;

	m = 0;
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	tmp = ft_split_parsing(line, ' ');
	tmp = ft_arg(tmp, env);
	while (tmp && tmp[index])
	{
		tab[m] = ft_strdup(tmp[index]);
		m++;
		index++;
	}
	tab[m] = NULL;
	ft_free(tmp, ft_tabsize(tmp));
	return (tab);
}

void	ft_echo_arg(char *line, char **env, t_pars *tab)
{
	char	**tmp;
	int		i;
	int		n;
	int		start;

	n = 0;
	i = 1;
	tmp = ft_split_parsing(line, ' ');
	tmp = ft_arg(tmp, env);
	while (check_is_opt_echo(tmp[i]))
	{
		i++;
		n = 1;
	}
	tab->option = ft_echo_option(n);
	n = 0;
	start = i;
	while (tmp && tmp[i])
	{
		i++;
		n++;
	}
	tab->arg = return_arg(line, env, n, start);
	ft_free(tmp, ft_tabsize(tmp));
}

void	get_arg(char *line, char *cmd, char **env, t_pars *tab)
{
	char	**tmp;
	int		i;
	int		n;
	int		start;

	n = 0;
	i = 0;
	if (!cmd)
		return ;
	if (cmd && (ft_strncmp(cmd, "echo", 5) == 0))
		return (ft_echo_arg(line, env, tab));
	tmp = ft_split_parsing(line, ' ');
	tmp = ft_arg(tmp, env);
	while (check_is_opt(tmp[++i]) && (ft_strncmp(cmd, "exit", 4)))
		n++;
	tab->option = get_opt(line, n, env);
	if (n > 1)
		tab->regroup_exit = 1;
	n = 0;
	start = i;
	while (tmp && tmp[i++])
		n++;
	tab->arg = return_arg(line, env, n, start);
	ft_free(tmp, ft_tabsize(tmp));
}
