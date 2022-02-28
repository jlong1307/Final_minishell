/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:27:09 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/07 14:39:22 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*char_s;
	unsigned char	char_c;
	size_t			i;

	i = 0;
	if (s == NULL)
		return (NULL);
	char_s = (unsigned char *) s;
	char_c = (unsigned char) c;
	while (i < n)
	{
		if (char_s[i] == char_c)
			return (&char_s[i]);
		i++;
	}
	return (NULL);
}
