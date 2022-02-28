/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:29:47 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/07 14:39:57 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*char_s;
	char	char_c;
	int		pos_c;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	char_s = (char *) s;
	char_c = (char) c;
	pos_c = -1;
	while (char_s[i])
	{
		if (char_s[i] == char_c)
			pos_c = i;
		i++;
	}
	if (!char_c)
		return (&char_s[i]);
	if (pos_c != -1)
		return (&char_s[pos_c]);
	return (NULL);
}
