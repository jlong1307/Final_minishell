/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:04:13 by jvander-          #+#    #+#             */
/*   Updated: 2021/07/07 08:37:06 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbr_char(int n)
{
	int			res;
	long long	nbr;

	res = 0;
	nbr = n;
	if (n <= 0)
	{
		nbr = -nbr;
		res++;
	}
	while (nbr > 0)
	{
		res++;
		nbr /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char		*int_char;
	int			char_len;
	long long	nbr;

	nbr = n;
	char_len = ft_nbr_char(n);
	int_char = malloc(sizeof(char) * char_len + 1);
	if (int_char == NULL)
		return (NULL);
	int_char[char_len] = '\0';
	if (n < 0)
	{
		nbr = -nbr;
		int_char[0] = '-';
	}
	if (n == 0)
		int_char[0] = '0';
	while (nbr > 0)
	{
		int_char[char_len - 1] = nbr % 10 + '0';
		nbr /= 10;
		char_len --;
	}
	return (int_char);
}
