/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:45:28 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/20 16:10:50 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

/*
	arg == char ** avec plusieurs arg
	=> char * cmd
	=> char * opt
	=> faire un tab taille n pour arg
	=> size == cmd + opt + taille arg * taille char *
*/

static int	ft_size_cmd(t_exc cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd.cmd)
		i++;
	if (cmd.opt)
		i++;
	if (cmd.arg)
	{
		while (cmd.arg[j++])
			i++;
	}
	return (i + 1);
}

char	**create_cmd(t_exc command)
{
	char	**to_ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	to_ret = (char **)malloc(sizeof(char *) * ft_size_cmd(command));
	if (!to_ret)
		return (NULL);
	if (command.cmd)
		to_ret[i++] = command.cmd;
	if (command.opt)
		to_ret[i++] = command.opt;
	if (command.arg)
	{
		while (command.arg[j])
			to_ret[i++] = command.arg[j++];
	}
	to_ret[i] = NULL;
	return (to_ret);
}

int	ft_check_exist(char *cmd)
{
	int	i;

	i = 0;
	if (cmd && cmd[i] == '/')
	{
		while (cmd[++i] == '/' && cmd[i])
			;
	}
	else
		return (1);
	while (cmd[++i] && cmd[i] != '/')
		;
	if (i == (int)ft_strlen(cmd))
		return (0);
	return (1);
}
