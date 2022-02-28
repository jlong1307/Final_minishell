/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:06:39 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/24 14:46:21 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

extern t_global	g_global;

int	ft_error_pipe(void)
{
	if (g_global.fork_pid == -1)
	{
		ft_perror("fork", NULL, "Resource temporarily unavailable");
		g_global.exit_code = 1;
		return (1);
	}
	return (0);
}

static int	ft_check_no_need_opt(t_exc exc)
{
	if (check_builtin(exc.cmd) == ECHO)
		return (0);
	return (1);
}

static int	ft_check_no_need_arg(t_exc exc)
{
	if (check_builtin(exc.cmd) == PWD)
		return (1);
	if (check_builtin(exc.cmd) == ENV)
		return (1);
	return (0);
}

int	ft_check_error_arg_opt(t_exc exc)
{
	int	error;

	error = 0;
	if (check_builtin(exc.cmd) == EXIT)
		return (0);
	if (ft_tabsize(exc.arg) && ft_check_no_need_arg(exc))
	{
		ft_perror(exc.cmd, NULL, "doesn't take argument");
		error = 1;
	}
	if (exc.opt && ft_check_no_need_opt(exc))
	{
		ft_perror(exc.cmd, NULL, "doesn't take opt");
		error = 1;
	}
	if (error)
	{
		g_global.exit_code = 1;
		return (1);
	}
	return (0);
}
