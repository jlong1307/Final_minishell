/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:50 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/02 16:13:01 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	ft_simple(char *heredoc)
{
	int		fd;
	char	*line;

	fd = open("/tmp/heredoc.txt", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_perror("open", NULL, "Error open heredoc");
		g_global.exit_code = 1;
		return ;
	}
	rl_on_new_line();
	line = readline("> ");
	if (ft_strcmp(line, heredoc) == 0)
		return (free(line));
	ft_putendl_fd(line, fd);
	while (ft_strcmp(line, heredoc) != 0)
	{
		free(line);
		rl_on_new_line();
		line = readline("> ");
		if (ft_strcmp(line, heredoc) != 0)
			ft_putendl_fd(line, fd);
	}
	free(line);
	close(fd);
}

int	ft_heredoc(t_exc cmd)
{
	int	i;
	int	status;

	if (cmd.heredoc == NULL)
		return (EXIT_SUCCESS);
	g_global.in_heredoc = 1;
	g_global.fork_pid = fork();
	if (g_global.fork_pid == -1)
		exit (EXIT_FAILURE);
	if (g_global.fork_pid == 0)
	{
		ft_set_signal();
		i = -1;
		while (cmd.heredoc[++i] && g_global.exit_code == 0)
			ft_simple(cmd.heredoc[i]);
		exit(g_global.exit_code);
	}
	waitpid(0, &status, 0);
	g_global.in_heredoc = 0;
	return (0);
}
