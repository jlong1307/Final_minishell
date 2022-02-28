/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:34:10 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/07 14:58:26 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*to_ret;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	to_ret = malloc(count * size);
	if (!to_ret)
		return (NULL);
	ft_bzero(to_ret, size * count);
	return (to_ret);
}
