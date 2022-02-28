/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:34:37 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/07 12:03:05 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			next = (*lst)->next;
			ft_lstdelone((*lst), del);
			*lst = next;
		}
	}
}
