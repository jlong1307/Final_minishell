/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:38:42 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/19 15:40:24 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_free_tab_exc(t_exc *last_tab, t_pars *tab)
{
	int	i;

	i = -1;
	if (last_tab)
	{
		while (tab && ++i <= tab->pipe)
		{
			if (last_tab[i].cmd)
				free(last_tab[i].cmd);
			if (last_tab[i].opt)
				free(last_tab[i].opt);
			if (last_tab[i].redirect)
				ft_free(last_tab[i].redirect, ft_tabsize(last_tab[i].redirect));
			if (last_tab[i].arg)
				ft_free(last_tab[i].arg, ft_tabsize(last_tab[i].arg));
			if (last_tab[i].heredoc)
				ft_free(last_tab[i].heredoc, ft_tabsize(last_tab[i].heredoc));
		}
	}
	free(tab);
	free(last_tab);
}
