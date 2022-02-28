/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_untils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:22 by jlong             #+#    #+#             */
/*   Updated: 2022/02/01 15:46:57 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	ft_get_index(char *s)
{
	int		i;
	char	*line;

	line = strdup(s);
	line = ft_strtrim(line, " \t");
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<')
		{
			free(line);
			return (1);
		}
		i++;
	}
	free(line);
	return (0);
}

void	init_ptn(t_exc *tab)
{
	tab->cmd = NULL;
	tab->opt = NULL;
	tab->arg = NULL;
	tab->input = NULL;
	tab->output = NULL;
	tab->redirect = NULL;
	tab->heredoc = NULL;
}

void	init_tmp(t_tmp *tmp)
{
	tmp->tmp = NULL;
	tmp->rest = NULL;
	tmp->new_line = NULL;
	tmp->n = 0;
	tmp->m = 0;
	tmp->nl = NULL;
	tmp->var = NULL;
}

int	*get_index(char *line, size_t size, char c)
{
	int	i;
	int	j;
	int	*p_tab;

	j = 0;
	i = 0;
	p_tab = 0;
	p_tab = malloc(sizeof(int *) * (size + 1));
	if (!p_tab)
		exit(EXIT_FAILURE);
	while (line[i] != '\0')
	{
		if (c == '-' && line[i] == '-' && line[i -1] != ' ')
			i++;
		if (line[i] == c && check_quote(line, i))
			p_tab[j++] = i;
		i++;
	}
	p_tab[j] = -1;
	return (p_tab);
}

char	*our_getenv(char *line, char **env)
{
	int		index;
	char	*var;
	char	*tmp;
	char	**test;

	var = NULL;
	test = NULL;
	tmp = NULL;
	index = find_var_in_env(line, env);
	if (index >= 0)
	{
		var = env[index];
		test = ft_split(var, '=');
		if (ft_tabsize(test) > 1)
			tmp = ft_strdup(test[1]);
	}
	if (index == -1)
		tmp = ft_strdup("");
	ft_free(test, ft_tabsize(test));
	free(line);
	return (ft_strtrim(tmp, " "));
}
