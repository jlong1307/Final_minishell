/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:53 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/24 12:19:48 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	ft_set_output_file(char *output)
{
	int	fd;

	if (ft_strncmp(output, ">>", 2) == 0)
		fd = open(output + 2, O_WRONLY | O_APPEND, 0644);
	else
		fd = open(output + 1, O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_perror("open", output, "Impossible to open file");
		g_global.exit_code = EXIT_FAILURE;
		exit(g_global.exit_code);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_perror("dup2", NULL, "Impossible to clone output file");
		g_global.exit_code = EXIT_FAILURE;
		exit(g_global.exit_code);
	}
	if (close(fd) == -1)
	{
		ft_perror("close", NULL, "Impossible to close output file");
		g_global.exit_code = EXIT_FAILURE;
		exit(g_global.exit_code);
	}
}

static void	ft_set_input_file(char *input)
{
	int	fd;

	fd = open(input + 1, O_RDONLY);
	if (fd == -1)
	{
		ft_perror("open", input, "Impossible to open file");
		g_global.exit_code = EXIT_FAILURE;
		exit(g_global.exit_code);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_perror("dup2", NULL, "Impossible to clone input file");
		g_global.exit_code = EXIT_FAILURE;
		exit(g_global.exit_code);
	}
	if (close(fd) == -1)
	{
		ft_perror("close", NULL, "Impossible to close input file");
		g_global.exit_code = EXIT_FAILURE;
		exit(g_global.exit_code);
	}
}

static void	ft_open_tmp(t_exc cmd)
{
	int	fd;

	if (cmd.heredoc)
	{
		fd = open("/tmp/heredoc.txt", O_RDWR | O_CREAT, 0644);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			ft_perror("dup2", NULL, "Error dup2 STDIN");
			g_global.exit_code = EXIT_FAILURE;
			exit(g_global.exit_code);
		}
		if (close(fd) == -1)
		{
			ft_perror("close", NULL, "Error close file");
			g_global.exit_code = EXIT_FAILURE;
			exit(g_global.exit_code);
		}
	}
}

void	ft_redirect_input(t_exc cmd, int n_pipe, int *fds)
{
	char	*input;

	ft_open_tmp(cmd);
	input = ft_get_last_input(cmd);
	if (input)
		ft_set_input_file(input);
	if (n_pipe != 0)
	{
		if (!ft_get_last_input(cmd))
		{
			if (dup2(fds[n_pipe - 2], STDIN_FILENO) == -1)
			{
				ft_perror("dup2", NULL, "Error dup2 STDIN");
				g_global.exit_code = EXIT_FAILURE;
				exit(g_global.exit_code);
			}
		}
	}
}

void	ft_redirect_output(t_exc cmd, int n_pipe, int *fds, int nbr_pipe)
{
	char	*output;

	output = ft_get_last_output(cmd);
	if (output)
		ft_set_output_file(output);
	if ((n_pipe / 2) < nbr_pipe)
	{
		if (!ft_get_last_output(cmd))
		{
			if (dup2(fds[n_pipe + 1], STDOUT_FILENO) == -1)
			{
				ft_perror("dup2", NULL, "Error dup2 STDOUT");
				g_global.exit_code = EXIT_FAILURE;
			}
		}
	}
}
