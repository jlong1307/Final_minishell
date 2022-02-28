/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:59 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/02 15:00:17 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

t_global	g_global;

static void	ft_execute_line(t_exc *exc, t_pars *tab, char ***new_env)
{
	int	*fds;

	ft_open_pipes(tab->pipe, &fds);
	ft_exec_heredoc(tab->pipe, exc);
	ft_create_all_redirect(exc, tab->pipe);
	if ((g_global.exit_code == 1 && check_builtin(exc[0].cmd) != EXIT))
		return (ft_close_pipes(tab->pipe, fds));
	if (tab->pipe == 0 && check_builtin(exc[0].cmd) == EXIT)
	{
		ft_free(*new_env, ft_tabsize(*new_env));
		ft_exit(exc[0], tab->pipe);
		ft_free_tab_exc(exc, tab);
		exit(g_global.exit_code);
	}
	if (check_builtin(exc->cmd) != ECHO)
		g_global.exit_code = 0;
	if (tab->pipe == 0 && (check_builtin(exc[0].cmd) == CD
			|| check_builtin(exc[0].cmd) == EXPORT
			|| check_builtin(exc[0].cmd) == UNSET))
		ft_execute_command(exc[0], new_env, tab->pipe);
	else
		ft_execute_pipe(exc, tab->pipe, new_env, fds);
	free(fds);
}

void	ft_prompt(t_state *state)
{
	g_global.fork_pid = 0;
	init_struct(state);
	rl_on_new_line();
	(state)->line = readline("\x1b[34mminishell > \x1b[0m");
	add_history(state->line);
	ft_ctrl_d(state);
	if (state && state->line[0] == '\0')
	{
		free(state->line);
		state->line = NULL;
	}
}

static void	ft_minishell(t_pars	*tab, t_exc *exc, char ***new_env)
{
	if (tab)
	{
		exc = last_parsing(tab, *new_env);
		ft_execute_line(exc, tab, new_env);
		ft_free_tab_exc(exc, tab);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_state	*state;
	char	**new_env;
	t_pars	*tab;
	t_exc	*exc;

	if (argc > 1)
	{
		ft_perror(argv[1], NULL, "No such file or directory");
		return (127);
	}
	new_env = cpy_env(env);
	init_variables(&state, &tab, &exc);
	update_shlvl(&new_env);
	ft_signal();
	while (1)
	{
		ft_prompt(state);
		if (state->line && state->line[0] != '\0')
		{
			tab = parsing(state, new_env);
			ft_minishell(tab, exc, &new_env);
		}
	}
	return (0);
}
