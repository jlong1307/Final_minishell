/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:48:08 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 11:48:27 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	**split_command(char *line)
{
	char	**command;

	command = ft_split(line, ' ');
	if (!command)
		return (NULL);
	if (!ft_strncmp(command[0], "cd", 2))
		return (ft_free(command, ft_tabsize(command)));
	return (command);
}
