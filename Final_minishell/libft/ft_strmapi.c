/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:31:31 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/05 14:01:57 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str_to_ret;
	int		str_len;
	int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	str_to_ret = malloc(sizeof(char) * str_len + 1);
	if (str_to_ret == NULL)
		return (NULL);
	str_to_ret[str_len] = '\0';
	i = 0;
	while (s[i])
	{
		str_to_ret[i] = (*f)(i, s[i]);
		i++;
	}	
	return (str_to_ret);
}
