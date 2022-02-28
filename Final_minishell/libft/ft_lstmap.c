/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:25:40 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/21 11:29:27 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*to_ret;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	to_ret = ft_lstnew(f(lst->content));
	if (to_ret == NULL)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp == NULL)
			ft_lstclear(&temp, del);
		ft_lstadd_back(&to_ret, temp);
		lst = lst->next;
	}
	return (to_ret);
}
