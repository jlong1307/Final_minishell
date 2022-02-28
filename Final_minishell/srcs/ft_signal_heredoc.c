/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:56 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/20 15:00:15 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	ft_handler_heredoc(int sig_code)
{
	if (!g_global.fork_pid)
	{
		if (sig_code == SIGINT)
		{
			g_global.exit_code = 1;
			exit(1);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else
		if (sig_code == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_set_signal(void)
{
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, ft_handler_heredoc);
}
