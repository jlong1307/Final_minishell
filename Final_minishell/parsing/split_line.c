/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:33 by jlong             #+#    #+#             */
/*   Updated: 2022/01/24 13:21:48 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	split_pipe(t_state *s)
{
	int	i;
	int	start;
	int	next;

	i = 0;
	start = 0;
	next = 0;
	if (s->pipe[i] != -1)
	{
		while (s->pipe[i] != -1)
		{
			next = s->pipe[i] - start;
			s->cm[i] = ft_substr(s->line, start, next);
			s->cm[i] = ft_strtrim(s->cm[i], " ");
			start = s->pipe[i] + 1;
			i++;
		}
	}
	next = s->eof;
	s->cm[i] = ft_substr(s->line, start, next);
	s->cm[i] = ft_strtrim(s->cm[i], " ");
}

t_pars	*split_line(t_state *s, char **env)
{
	t_pars	*tab;

	tab = NULL;
	s->cm = malloc(sizeof(char *) * (s->n_of_pipe + 1));
	if (!s->cm)
		exit(EXIT_FAILURE);
	split_pipe(s);
	tab = find_command(s, env);
	return (tab);
}
