/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:36:17 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/02 16:11:38 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

char	*our_getenv_bis(char *line, char **env)
{
	int		index;
	char	*var;
	char	*tmp;
	char	**test;

	var = NULL;
	test = NULL;
	tmp = NULL;
	index = find_var_in_env(line, env);
	if (index >= 0)
	{
		var = env[index];
		test = ft_split(var, '=');
		if (ft_tabsize(test) > 1)
			tmp = ft_strdup(test[1]);
	}
	if (index == -1)
		tmp = ft_strdup("");
	index = -1;
	while (test && test[++index])
		free(test[index]);
	if (test)
		free(test);
	free(line);
	return (ft_strtrim(tmp, " "));
}

static int	ft_check_nbr(char *nbr)
{
	if (nbr[0] == '-' && ft_strlen(nbr) > 20)
		return (1);
	if (nbr[0] != '-' && ft_strlen(nbr) > 19)
		return (1);
	if (nbr[0] == '-' && ft_strlen(nbr) < 20)
		return (0);
	if (nbr[0] != '-' && ft_strlen(nbr) < 19)
		return (0);
	if (nbr[0] == '-')
		return (ft_strncmp(nbr, LONG_MIN_CHAR, ft_strlen(nbr)));
	return (ft_strncmp(nbr, LONG_MAX_CHAR, ft_strlen(nbr)));
}

void	ft_exit(t_exc exc, int nbr_pipe)
{
	int	i;

	i = -1;
	if (nbr_pipe == 0)
		printf("exit\n");
	while (exc.arg && exc.arg[++i])
	{
		if (exc.arg[i] && (!check_opt_is_valid(exc.arg[i])
				|| (check_str_digit(exc.arg[i])
					|| ft_check_nbr(exc.arg[i]) != 0)))
		{
			ft_perror(exc.cmd, exc.arg[0], "numeric argument required");
			g_global.exit_code = 255;
			return ;
		}
	}
	if (i > 1)
	{
		ft_perror(exc.cmd, NULL, "too many arguments");
		g_global.exit_code = 1;
		return ;
	}
	if (exc.arg)
		g_global.exit_code = ft_atoi(exc.arg[0])
			- (256 * (ft_atoi(exc.arg[0]) / 256));
}
