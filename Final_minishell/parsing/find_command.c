/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:20:55 by jlong             #+#    #+#             */
/*   Updated: 2022/02/02 15:26:26 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	tab->heredoc = NULL;
	tab->next_char = NULL;
	tab->redirect = NULL;
	tab->regroup_exit = 0;
}

char	*ft_get_command(char *line, char **env)
{
	char	**split;
	t_tmp	tmp;
	char	*l;

	l = strdup(line);
	l = ft_strtrim(l, " \t");
	init_tmp(&tmp);
	split = ft_split_parsing(l, ' ');
	if (l[0])
	{
		tmp.tmp = ft_strdup(split[0]);
		tmp.new_line = ft_arg_bis(tmp.tmp, env);
	}
	ft_free(split, ft_tabsize(split));
	free(l);
	return (tmp.new_line);
}

t_pars	get_command(char *line, t_state *s, char **env)
{
	t_pars	tab;
	char	*new_line;

	init_tab(&tab);
	new_line = NULL;
	(void)s;
	if (ft_get_index(line))
	{
		new_line = get_heredoc(line, &tab);
		new_line = get_redirect(new_line, &tab);
	}
	else
	{
		tab.command = ft_substr(line, 0, ft_strlen(line));
		tab.command = ft_arg_bis(ft_strtrim(tab.command, " \t"), env);
	}
	if (new_line)
	{
		tab.command = ft_get_command(new_line, env);
		get_arg(new_line, tab.command, env, &tab);
	}
	free(new_line);
	return (tab);
}

t_pars	*find_command(t_state *s, char **env)
{
	int		i;
	t_pars	*comd;

	i = -1;
	comd = malloc(sizeof(t_pars) * (s->n_of_pipe + 1));
	if (!comd)
		exit(EXIT_FAILURE);
	while (++i <= s->n_of_pipe)
		comd[i] = get_command(s->cm[i], s, env);
	return (comd);
}

int	ft_check_command(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isalnum(line[i]))
			return (0);
		i++;
	}
	return (1);
}
