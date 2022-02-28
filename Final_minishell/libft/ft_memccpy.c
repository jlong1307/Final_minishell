/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:25:36 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/06 14:30:17 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*zsrc;
	unsigned char	*zdst;

	i = 0;
	zsrc = (unsigned char *)src;
	zdst = (unsigned char *)dst;
	while (i < n)
	{
		zdst[i] = zsrc[i];
		if (zsrc[i] == (unsigned char)c)
			return ((void *)&zdst[i + 1]);
		i++;
	}
	return (NULL);
}
