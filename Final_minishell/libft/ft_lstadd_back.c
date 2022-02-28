/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:15:01 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/21 11:36:34 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (alst != NULL)
	{
		temp = *alst;
		if (temp != NULL && new != NULL)
		{
			while (temp->next != NULL)
			{
				temp = temp->next;
			}	
			temp->next = new;
		}
		if (*alst == NULL)
			*alst = new;
	}
}
