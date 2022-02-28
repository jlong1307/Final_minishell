/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:20:58 by jlong             #+#    #+#             */
/*   Updated: 2022/01/19 16:36:46 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*ft_strjoin_double_free(char *s1, char *s2)
{
	size_t	count;
	char	*new_str;

	if (s1 == NULL)
		s1 = ft_calloc(1, sizeof(char));
	if (s1 == NULL || s2 == NULL)
	{
		free(s1);
		return (NULL);
	}
	count = -1;
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		exit(EXIT_FAILURE);
	while (s1[++count])
		new_str[count] = s1[count];
	count = -1;
	while (s2[++count])
		new_str[count + ft_strlen(s1)] = s2[count];
	new_str[count + ft_strlen(s1)] = '\0';
	free(s1);
	s1 = NULL;
	return (new_str);
}
