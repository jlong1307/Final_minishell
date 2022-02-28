/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:28:38 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/19 15:52:10 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*char_s;
	char	char_c;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	char_c = (char) c;
	char_s = (char *) s;
	while (char_s[i])
	{
		if (char_s[i] == char_c)
			return (&char_s[i]);
		i++;
	}
	if (c == '\0')
		return (&char_s[i]);
	return (NULL);
}
