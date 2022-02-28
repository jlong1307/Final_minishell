/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:23:45 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/21 18:04:00 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

char	**ft_realloc_env(char ***env, int size)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (ft_tabsize((*env)) + size));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	return (new_env);
}

static char	*parse_arg(char *arg)
{
	char	*res;
	int		i;

	res = ft_strtrim_modified(arg, "\"");
	arg = NULL;
	i = -1;
	while (res[++i])
	{
		if ((!ft_isalpha(res[i]) || !ft_isalnum(res[i])) && res[i] != '_')
		{
			ft_perror("unset", res, "not a valid identifier");
			g_global.exit_code = 1;
			return (NULL);
		}
	}
	return (res);
}

/*
*	LEAKS ligne 56 ; new_env[++k] = ft_strdup((*env)[j]);
*/
static void	create_new_env(t_exc exc, char ***env, int i)
{
	char	**new_env;
	int		j;
	int		k;

	new_env = ft_calloc(sizeof(char *), (ft_tabsize(*env) + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	j = -1;
	k = -1;
	while ((*env)[++j])
	{
		if (j == find_var_in_env(exc.arg[i], *env))
			j++;
		new_env[++k] = ft_strdup((*env)[j]);
		if (!new_env[k])
			exit(EXIT_FAILURE);
	}
	new_env[j] = NULL;
	ft_free(*env, ft_tabsize(*env));
	*env = new_env;
}

int	ft_unset(t_exc exc, char ***env)
{
	int		i;

	i = -1;
	g_global.exit_code = 0;
	if (exc.arg)
	{
		while (exc.arg[++i])
		{
			exc.arg[i] = parse_arg(exc.arg[i]);
			if (exc.arg[i] && find_var_in_env(exc.arg[i], *env))
				create_new_env(exc, env, i);
		}
	}
	return (UNSET);
}
