/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:32:04 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/08 11:42:55 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dst == NULL || src == NULL)
		return (-1);
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (src_len + dstsize);
	while (src[i] && (dst_len + i) < dstsize)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	if ((dst_len + i) == dstsize && dstsize > dst_len)
	{
		dst[dst_len + i - 1] = '\0';
	}
	else
		dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}
