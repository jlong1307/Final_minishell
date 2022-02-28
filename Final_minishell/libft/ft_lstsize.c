/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:04:25 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/21 11:31:55 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		res;
	t_list	*temp;

	if (lst == NULL)
		return (0);
	res = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		res++;
	}
	return (res);
}
