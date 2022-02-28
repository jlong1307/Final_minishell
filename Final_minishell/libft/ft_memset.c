/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:23:32 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/02 12:23:17 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;
	char	*char_b;

	if (b == NULL)
		return (NULL);
	char_b = (char *) b;
	i = 0;
	while (i < n)
	{
		char_b[i] = c;
		i++;
	}
	return (b);
}
