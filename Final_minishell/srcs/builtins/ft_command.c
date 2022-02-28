/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:23:37 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/20 14:59:34 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

static void	ft_print_line(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(t_exc exc)
{
	if (exc.opt && ft_strchr(exc.opt, 'n'))
		ft_print_line(exc.arg);
	else if (ft_tabsize(exc.arg) < 1)
		ft_putchar_fd('\n', 1);
	else
	{
		ft_print_line(exc.arg);
		printf("\n");
	}
	g_global.exit_code = 0;
	return (ECHO);
}

int	ft_pwd(void)
{
	char	pwd[1024];

	g_global.exit_code = 0;
	if (!getcwd(pwd, 1024))
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		g_global.exit_code = 1;
	}
	else
		printf("%s\n", pwd);
	return (PWD);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	g_global.exit_code = 0;
	while (i < ft_tabsize(env))
	{
		if (ft_strchr_modified(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (ENV);
}
