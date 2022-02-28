/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:15 by jlong             #+#    #+#             */
/*   Updated: 2022/01/26 12:47:00 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	nbr_of_redirect(char *line)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (check_quote(line, i) && (line[i] == '<' || line[i] == '>'))
			n++;
		i++;
	}
	return (n);
}

void	count_char_bis(t_tmp *tmp, char *line)
{
	while (line[tmp->n] && (line[tmp->n] == '<' || line[tmp->n] == '>'))
	{
		tmp->n++;
		tmp->m++;
	}
	if (tmp->n >= (int)ft_strlen(line))
		return ;
	while (line[tmp->n] && (line[tmp->n] == ' ' || line[tmp->n] == '\0'))
	{
		tmp->n++;
		tmp->m++;
	}
	if (tmp->n >= (int)ft_strlen(line))
		return ;
	while (line[tmp->n] && (ft_isascii(line[tmp->n])))
	{
		if (line[tmp->n] == '<' || line[tmp->n] == '>'
			|| line[tmp->n] == ' ' || line[tmp->n] == '\0')
			break ;
		tmp->n++;
		tmp->m++;
	}
}

char	*cut_redirect(char *line, int index, char **tab_here, char c)
{
	t_tmp	tmp;
	char	*symbole;

	init_tmp(&tmp);
	symbole = NULL;
	tmp.n = index;
	tmp.tmp = ft_substr(line, 0, index);
	count_char_bis(&tmp, line);
	tmp.rest = ft_substr(line, index + tmp.m, (ft_strlen(line) - index));
	tmp.new_line = ft_strjoin_double_free(tmp.tmp, "");
	tmp.new_line = ft_strjoin_double_free(tmp.new_line, tmp.rest);
	*tab_here = ft_substr(line, index + 1, tmp.m - 1);
	*tab_here = ft_strtrim(*tab_here, " ");
	if (c == '<')
		symbole = ft_strdup("<");
	else if (c == '>')
		symbole = ft_strdup(">");
	tmp.nl = ft_strjoin_double_free(symbole, *tab_here);
	free(*tab_here);
	*tab_here = NULL;
	*tab_here = tmp.nl;
	free(tmp.rest);
	return (tmp.new_line);
}

char	*get_tab_redirect(char *line, char **tab)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] && check_quote(line, i) && (line[i] == '<'
				|| line[i] == '>'))
		{
			new_line = cut_redirect(line, i, &tab[j], line[i]);
			j++;
			line = new_line;
			i = -1;
		}
		i++;
	}
	tab[j] = NULL;
	return (new_line);
}

char	*get_redirect(char *line, t_pars *tab_here)
{
	char	*new_line;
	int		nbr_of_here;
	char	**tab;
	char	*tmp;

	new_line = NULL;
	tab = NULL;
	nbr_of_here = 0;
	nbr_of_here = nbr_of_redirect(line);
	if (nbr_of_here < 1)
	{
		tmp = ft_strdup(line);
		free(line);
		return (tmp);
	}
	tab = malloc(sizeof(char *) * (nbr_of_here + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	new_line = get_tab_redirect(line, tab);
	tab_here->redirect = tab;
	tmp = ft_strtrim(new_line, " ");
	free(line);
	line = NULL;
	return (tmp);
}
