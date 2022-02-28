/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:20:50 by jlong             #+#    #+#             */
/*   Updated: 2022/01/26 12:44:37 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

extern t_global	g_global;

int	ft_check_char_syntax(t_state *s, char c, int i)
{
	int	count;

	count = 0;
	if (s->line[ft_strlen(s->line) - 1] == c)
		return (0);
	if (s->line[i] == c)
	{
		while (s->line[i] && s->line[i++] == c)
			count++;
		if (c == '|' && count > 1)
			return (0);
		else if (count > 2)
			return (0);
	}
	return (1);
}

void	ft_free_pars_tab(t_state *s)
{
	if (s->pipe)
		free(s->pipe);
	if (s->line)
		free(s->line);
}

void	ft_free_pars_error(t_state *s)
{
	int	nbr;

	nbr = 0;
	if (s->line)
		free(s->line);
	if (s->pipe)
		free(s->pipe);
	if (s->cm)
	{
		while (nbr <= s->n_of_pipe)
		{
			free(s->cm[nbr]);
			nbr++;
		}
	}
	if (s)
		free(s);
	g_global.exit_code = 1;
}

void	ft_error_malloc(t_state *s)
{
	int	nbr;

	nbr = 0;
	if (s->pipe)
		free(s->pipe);
	while (nbr <= s->n_of_pipe)
	{
		if (s->cm[nbr] != NULL || s->cm[nbr][0] == '\0')
			free(s->cm[nbr]);
		nbr++;
	}
	if (s->cm)
		free(s->cm);
	ft_perror("Malloc", NULL, "Error allocation memory");
}

void	check_all_string_bis_bis(char *line, t_tmp *tmp, char c, int index)
{
	int	i;

	i = return_index_all_string(line, index, c);
	if (index > 0)
		tmp->nl = ft_substr(line, 0, index - 1);
	else
		tmp->nl = ft_substr(line, 0, index);
	if (c == '\'' || c == '\"')
	{
		tmp->tmp = ft_substr(line, index, (i + 1) - index);
		tmp->rest = ft_substr(line, i, ((ft_strlen(line) - 1) - i));
	}
	else
	{
		tmp->tmp = ft_substr(line, index, i - index);
		tmp->rest = ft_substr(line, i, (ft_strlen(line) - i));
	}
}
