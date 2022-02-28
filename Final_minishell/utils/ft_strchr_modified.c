/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_modified.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:47:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 11:47:35 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	ft_strchr_modified(const char *s, int c)
{
	char	*char_s;
	char	char_c;
	int		i;

	i = 0;
	if (s == NULL)
		return (-1);
	char_c = (char) c;
	char_s = (char *) s;
	while (char_s[i])
	{
		if (char_s[i] == char_c)
			return (1);
		i++;
	}
	if (c == '\0' && char_s[i] == '\0')
		return (i);
	return (0);
}
