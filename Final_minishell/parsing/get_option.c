/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:10 by jlong             #+#    #+#             */
/*   Updated: 2022/01/21 15:45:46 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	**ft_echo_option(int n)
{
	char	**tmp;

	tmp = NULL;
	tmp = malloc(sizeof(char *) * (n + 1));
	if (!tmp)
		exit(EXIT_FAILURE);
	if (n == 1)
	{
		tmp[0] = ft_strdup("-n");
		tmp[1] = NULL;
	}
	else
		tmp[0] = NULL;
	return (tmp);
}

int	check_opt_is_valid(char	*line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-' && !ft_isalnum(line[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

char	**get_opt(char *line, int n, char **env)
{
	char	**tmp;
	int		i;
	int		m;
	char	**tab;

	i = 0;
	m = 0;
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	if (n >= 1)
	{
		tmp = ft_split_parsing(line, ' ');
		tmp = ft_arg(tmp, env);
		while (tmp && check_is_opt(tmp[++i]))
		{
			tab[m] = ft_strdup(tmp[i]);
			if (check_opt_is_valid(tab[m]))
				tab[m] = ft_strtrim(tab[m], "- ");
			m++;
		}
		ft_free(tmp, ft_tabsize(tmp));
	}
	tab[m] = NULL;
	return (tab);
}
