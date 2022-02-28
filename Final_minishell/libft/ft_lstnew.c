/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:28:21 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/07 10:52:41 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*to_ret;

	to_ret = malloc(sizeof(t_list));
	if (to_ret == NULL)
		return (NULL);
	to_ret->content = content;
	to_ret->next = NULL;
	return (to_ret);
}
