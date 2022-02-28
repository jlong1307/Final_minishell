/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:47:01 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 11:47:10 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*ft_get_last_input(t_exc cmd)
{
	char	**current;
	int		i;
	char	*input_file;

	i = -1;
	input_file = NULL;
	current = cmd.redirect;
	while (current && current[++i])
	{
		if (ft_strncmp(current[i], "<", 1) == 0)
			input_file = current[i];
	}
	return (input_file);
}

char	*ft_get_last_output(t_exc cmd)
{
	char	**current;
	int		i;
	char	*output_file;

	i = -1;
	output_file = NULL;
	current = cmd.redirect;
	while (current && current[++i])
	{
		if (ft_strncmp(current[i], ">>", 2) == 0)
			output_file = current[i];
		else if (ft_strncmp(current[i], ">", 1) == 0)
			output_file = current[i];
	}
	return (output_file);
}
