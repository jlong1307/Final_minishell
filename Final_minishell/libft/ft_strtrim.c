/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:41:17 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/14 17:51:42 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	j;
	size_t	i;
	char	*line;

	i = 0;
	if (!set || !s1)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	j = ft_strlen(&s1[i]);
	if (j != 0)
		while (s1[i + j - 1] && ft_strchr(set, s1[i + j - 1]) != NULL)
			j--;
	line = ft_substr(s1, i, j);
	free(s1);
	s1 = NULL;
	return (line);
}
