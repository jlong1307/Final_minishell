/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:38 by jlong             #+#    #+#             */
/*   Updated: 2022/01/13 13:13:23 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static int	ft_count_words(char *s, char c)
{
	int		i;
	int		nbr_words;

	i = 1;
	nbr_words = 0;
	if (s == NULL || s[0] == 0)
		return (0);
	if (s[0] != c)
		nbr_words++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c && check_quote(s, i))
			nbr_words++;
		i++;
	}
	return (nbr_words);
}

static int	ft_wordlen(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		if (s[i] == c && !check_quote(s, i))
		{
			while (s[i] == c && !check_quote(s, i))
				i++;
		}
	}
	return (i);
}

static char	*ft_strncpy(char *s, int size)
{
	char	*to_ret;

	to_ret = malloc(sizeof(char) * (size + 1));
	if (to_ret == NULL)
		exit(EXIT_FAILURE);
	to_ret[size] = '\0';
	size--;
	while (size >= 0 && s[size])
	{
		to_ret[size] = s[size];
		size--;
	}
	return (to_ret);
}

char	**ft_freee(char **s, int len_tab)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (i < len_tab && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split_parsing(char *s, char c)
{
	char	**to_ret;
	int		nbr_words;
	int		i;
	int		size_word;
	int		j;

	if (s == NULL)
		return (NULL);
	nbr_words = ft_count_words(s, c);
	to_ret = ft_calloc((nbr_words + 1), sizeof(char *));
	if (to_ret == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (j < nbr_words)
	{
		while (s[i] && s[i] == c && check_quote(s, i))
			i++;
		size_word = ft_wordlen(s + i, c);
		to_ret[j++] = ft_strncpy(s + i, size_word);
		if (to_ret[j - 1] == NULL)
			return (ft_free(to_ret, nbr_words + 1));
		i += size_word;
	}
	return (to_ret);
}
