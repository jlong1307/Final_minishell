/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:19 by jlong             #+#    #+#             */
/*   Updated: 2022/02/02 13:01:10 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*option(char **options)
{
	char	*line;
	int		i;
	int		size;

	size = 0;
	i = -1;
	if (options[0] == NULL)
	{
		free(options);
		return (NULL);
	}
	while (options[++i])
		size = size + ft_strlen(options[i]);
	line = malloc(sizeof(line) * (size + 2));
	if (!line)
		exit(EXIT_FAILURE);
	i = -1;
	line[0] = '-';
	line[1] = '\0';
	while (options[++i])
	{
		line = ft_strcat(line, options[i]);
	}
	ft_free(options, ft_tabsize(options));
	return (line);
}

char	*ft_command(char *command)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	if (!command)
		return (NULL);
	tmp = ft_strdup(command);
	while (tmp[i] != '\0')
	{
		tmp[i] = ft_tolower(tmp[i]);
		i++;
	}
	if ((ft_strncmp(tmp, "cd", 3)) == 0 || (ft_strncmp(tmp, "export", 6)) == 0
		|| !ft_check_command(tmp))
		new = ft_strdup(command);
	else
		new = ft_strdup(tmp);
	free(command);
	free(tmp);
	return (new);
}

char	*new_redirect(char *line)
{
	int		i;
	t_tmp	tmp;

	init_tmp(&tmp);
	i = 0;
	while (line[i] == '>' || line[i] == '<')
		i++;
	tmp.tmp = ft_substr(line, 0, i);
	while (line[i] && line[i] == ' ')
		i++;
	tmp.n = i;
	while (line[i] && ft_isascii(line[i]) && line[i] != ' ')
		i++;
	tmp.var = ft_substr(line, tmp.n, i - tmp.n);
	tmp.new_line = ft_strjoin_double_free(tmp.tmp, tmp.var);
	free(line);
	line = NULL;
	free(tmp.var);
	return (tmp.new_line);
}

char	**get_redirect_bis(char **tab_redirect, char **env)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab_redirect[i])
	{
		tab_redirect[i] = new_redirect(tab_redirect[i]);
		i++;
	}
	i = 0;
	while (tab_redirect[i])
	{
		if (ft_strncmp(tab_redirect[i], ">>", 2) == 0)
			tab_redirect[i] = get_var_env_bis(tab_redirect[i], env, 2);
		else if (ft_strncmp(tab_redirect[i], ">", 1) == 0)
			tab_redirect[i] = get_var_env_bis(tab_redirect[i], env, 1);
		else if (ft_strncmp(tab_redirect[i], "<", 1) == 0)
			tab_redirect[i] = get_var_env_bis(tab_redirect[i], env, 1);
		i++;
	}
	new_tab = tab_redirect;
	return (new_tab);
}

t_exc	*last_parsing(t_pars *tab, char **env)
{
	int		i;
	t_exc	*last_tab;

	last_tab = NULL;
	last_tab = malloc(sizeof(t_exc) * (tab->pipe + 1));
	if (!last_tab)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < tab->pipe + 1)
	{
		init_ptn(&last_tab[i]);
		if (tab[i].command)
			last_tab[i].cmd = ft_command(tab[i].command);
		if (tab[i].option)
			last_tab[i].opt = option(tab[i].option);
		if (tab[i].redirect)
			last_tab[i].redirect = get_redirect_bis(tab[i].redirect, env);
		if (tab[i].heredoc)
			last_tab[i].heredoc = tab[i].heredoc;
		if (tab[i].arg)
			last_tab[i].arg = tab[i].arg;
		last_tab[i].regroup_exit = tab[i].regroup_exit;
		i++;
	}
	return (last_tab);
}
