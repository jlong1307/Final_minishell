/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:29 by jlong             #+#    #+#             */
/*   Updated: 2022/01/24 13:21:14 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	init_quote(t_quote *quote)
{
	quote->simple_quote = 0;
	quote->double_quote = 0;
}

int	check_quote(char *line, int index)
{
	int		i;
	t_quote	quote;

	init_quote(&quote);
	i = -1;
	while (++i < index)
	{
		if (line[i] == '\'')
		{
			if (quote.simple_quote == 0 && quote.double_quote == 0)
				quote.simple_quote = 1;
			else
				quote.simple_quote = 0;
		}
		if (line[i] == '"')
		{
			if (quote.double_quote == 0 && quote.simple_quote == 0)
				quote.double_quote = 1;
			else
				quote.double_quote = 0;
		}		
	}
	if (quote.simple_quote == 0 && quote.double_quote == 0)
		return (1);
	return (0);
}

void	check_char(t_state *s)
{
	int	i;

	i = -1;
	while (s->line[++i] != '\0')
	{
		if (s->line[i] == '|' && check_quote(s->line, i))
			s->n_of_pipe++;
	}
	s->eof = i;
}

t_pars	*parsing(t_state *s, char **env)
{
	t_pars	*tab;

	tab = NULL;
	check_char(s);
	if (check_parsing(s))
	{
		tab = split_line(s, env);
		tab->pipe = s->n_of_pipe;
	}
	ft_free(s->cm, s->n_of_pipe + 1);
	ft_free_pars_tab(s);
	return (tab);
}
