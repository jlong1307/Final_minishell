/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:24:36 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/02 13:41:20 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	ft_create_all_exec(char ***folder, t_exc command)
{
	int	i;

	i = 0;
	if (!command.cmd)
		return (1);
	if (!(*folder))
		return (0);
	while ((*folder)[i])
	{
		(*folder)[i] = ft_strjoin_free((*folder)[i], "/");
		if (!(*folder)[i])
			return (0);
		(*folder)[i] = ft_strjoin_free((*folder)[i], command.cmd);
		if (!(*folder)[i])
			return (0);
		i++;
	}
	return (1);
}

static int	ft_free_exec(char **folder, char **cmd)
{
	ft_free(folder, ft_tabsize(folder));
	ft_free(cmd, ft_tabsize(cmd));
	return (EXIT_FAILURE);
}

static int	ft_try_exec(t_exc command, char **cmd, char **folder, char **env)
{
	int	i;

	i = -1;
	if (!ft_strlen(command.cmd) && ft_tabsize(command.heredoc)
		&& g_global.exit_code == 0)
		exit(EXIT_SUCCESS);
	if (ft_tabsize(command.heredoc) && g_global.exit_code == 1)
		exit(EXIT_FAILURE);
	if (!ft_strlen(command.cmd))
		exit(EXIT_SUCCESS);
	if (!ft_check_exist(command.cmd))
	{
		ft_perror(command.cmd, NULL, "no such file or directory");
		return (127);
	}
	while (folder[++i])
		g_global.exit_code = execve(folder[i], cmd, env);
	g_global.exit_code = execve(command.cmd, cmd, env);
	ft_perror(command.cmd, NULL, "command not found");
	return (127);
}

static int	ft_exec(t_exc command, char **env)
{
	char	**folder;
	char	**cmd;
	char	*line;

	ft_signal_msg();
	cmd = create_cmd(command);
	if (!cmd)
		exit (EXIT_FAILURE);
	line = our_getenv_bis(ft_strdup("PATH"), env);
	if (!line && ft_strlen(command.cmd) > 0)
	{
		ft_perror(command.cmd, NULL, "command not found");
		ft_free(cmd, ft_tabsize(cmd));
		return (127);
	}
	folder = ft_split(line, ':');
	if (!folder)
		return (ft_free_exec(folder, cmd));
	if (!ft_create_all_exec(&folder, command))
		return (ft_free_exec(folder, cmd));
	g_global.exit_code = ft_try_exec(command, cmd, folder, env);
	ft_free_exec(folder, cmd);
	if (line)
		free(line);
	return (g_global.exit_code);
}

int	execute(t_exc exc, char ***env, int nbr_pipe)
{
	if (check_builtin(exc.cmd) != 0)
	{
		ft_execute_command(exc, env, nbr_pipe);
		return (g_global.exit_code);
	}
	else
		return (ft_exec(exc, *env));
}
