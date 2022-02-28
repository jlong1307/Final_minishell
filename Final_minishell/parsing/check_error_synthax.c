/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_synthax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:42:52 by jlong             #+#    #+#             */
/*   Updated: 2022/02/02 14:52:39 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	check_error_syntax_bbbis(t_state *s)
{
	int	i;

	i = 0;
	while (s->line[i])
	{
		if (check_quote(s->line, i) && !ft_check_char_syntax(s, '<', i))
			return (0);
		if (check_quote(s->line, i) && !ft_check_char_syntax(s, '>', i))
			return (0);
		if (check_quote(s->line, i) && !ft_check_char_syntax(s, '|', i))
			return (0);
		i++;
	}
	return (1);
}

int	check_error_synthax(t_state *s)
{
	char	**tmp;
	int		i;
	int		error;

	i = -1;
	error = 0;
	tmp = ft_split_parsing(s->line, ' ');
	while (tmp && tmp[++i] != NULL)
	{
		if (tmp[i] && !ft_strncmp(tmp[i], ">>", 3) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "<<", 3) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "<", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], ">", 2) && tmp[i + 1] == NULL)
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "|", 2) && tmp[i + 1] == NULL)
			error = 1;
	}
	ft_free(tmp, ft_tabsize(tmp));
	if (error == 1)
		return (0);
	return (1);
}

int	check_error_synthax_bis(t_state *s)
{
	char	**tmp;
	int		i;
	int		error;

	i = -1;
	error = 0;
	tmp = ft_split_parsing(s->line, ' ');
	if (*tmp && *tmp[0] == '|')
	{
		ft_free(tmp, ft_tabsize(tmp));
		return (0);
	}
	while (tmp && tmp[++i] != NULL)
	{
		if (tmp[i] && !ft_strncmp(tmp[i], ">>>", 3))
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "<<<", 3))
			error = 1;
		else if (tmp[i] && !ft_strncmp(tmp[i], "||", 2))
			error = 1;
	}
	ft_free(tmp, ft_tabsize(tmp));
	if (error == 1)
		return (0);
	return (1);
}

int	check_error_synthax_bis_bis(t_state *s, char *l)
{
	char	**tmp;
	int		i;
	int		error;
	int		n;

	i = -1;
	error = 0;
	n = ft_strlen(l);
	tmp = ft_split_parsing(s->line, ' ');
	while (tmp && tmp[++i] != NULL)
	{
		if (!ft_strncmp(tmp[i], ">>", 3) && !ft_strncmp(tmp[i + 1], l, n))
			error = 1;
		else if (!ft_strncmp(tmp[i], "<<", 3) && !ft_strncmp(tmp[i + 1], l, n))
			error = 1;
		else if (!ft_strncmp(tmp[i], "<", 2) && !ft_strncmp(tmp[i + 1], l, n))
			error = 1;
		else if (!ft_strncmp(tmp[i], ">", 2) && !ft_strncmp(tmp[i + 1], l, n))
			error = 1;
	}
	ft_free(tmp, ft_tabsize(tmp));
	return (error);
}

int	check_parsing(t_state *s)
{
	if (!check_quote(s->line, s->eof))
	{
		ft_putendl_fd("syntax error near unexpected token \' or \"", 2);
		return (0);
	}
	if ((!check_error_synthax_bis(s)) || (!check_error_synthax(s))
		|| !check_error_syntax_bbbis(s))
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (0);
	}
	if (check_error_synthax_bis_bis(s, ">>")
		|| check_error_synthax_bis_bis(s, ">")
		|| check_error_synthax_bis_bis(s, "<")
		|| check_error_synthax_bis_bis(s, "<<")
		|| check_error_synthax_bis_bis(s, "|"))
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (0);
	}
	if (s->n_of_pipe >= 0)
		s->pipe = get_index(s->line, (s->n_of_pipe + 1), '|');
	return (1);
}
