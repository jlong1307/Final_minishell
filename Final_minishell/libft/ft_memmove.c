/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:26:18 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/06 14:30:44 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_char;
	const char	*src_char;

	dst_char = (char *) dst;
	src_char = (const char *) src;
	if (dst_char == NULL || src_char == NULL)
		return (NULL);
	if (src_char < dst_char)
	{
		while (len-- > 0)
			dst_char[len] = src_char[len];
	}
	else if (src_char > dst_char)
	{	
		while (len-- > 0)
			*dst_char++ = *src_char++;
	}
	return (dst);
}
