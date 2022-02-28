/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:22 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/20 15:00:22 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern t_global	g_global;

static void	init_global(void)
{
	g_global.exit_code = 0;
	g_global.fork_pid = 0;
	g_global.in_heredoc = 0;
}

void	init_struct(t_state *state)
{
	state->line = NULL;
	state->pipe = NULL;
	state->cm = NULL;
	state->n_of_pipe = 0;
	state->eof = 0;
}

void	init_variables(t_state **state, t_pars **tab, t_exc **exc)
{
	*tab = NULL;
	*state = NULL;
	*exc = NULL;
	*state = malloc(sizeof(t_state));
	if (!*state)
		exit(EXIT_FAILURE);
	init_global();
}
