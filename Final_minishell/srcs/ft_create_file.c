/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:30:45 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/24 12:20:29 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	ft_exit_create_file(char *file_name)
{
	g_global.exit_code = EXIT_FAILURE;
	if (file_name)
		free(file_name);
	return (g_global.exit_code);
}

static int	ft_create_file(char *name)
{
	char	*file_name;
	int		fd;

	file_name = ft_strdup(name);
	if (!file_name)
	{
		perror("malloc");
		return (ft_exit_create_file(file_name));
	}
	fd = open(file_name, O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_perror("open", file_name, "Impossible to open file");
		return (ft_exit_create_file(file_name));
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (ft_exit_create_file(file_name));
	}
	free(file_name);
	return (EXIT_SUCCESS);
}

static int	ft_create_file_trunc(char *name)
{
	char	*file_name;
	int		fd;

	file_name = ft_strdup(name);
	if (!file_name)
	{
		perror("malloc");
		return (ft_exit_create_file(file_name));
	}
	fd = open(file_name, O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_perror("open", file_name, "Impossible to open file");
		return (ft_exit_create_file(file_name));
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (ft_exit_create_file(file_name));
	}
	free(file_name);
	return (EXIT_SUCCESS);
}

static int	ft_create_redirect(t_exc exc)
{
	char	*current;
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (!exc.redirect || !ft_tabsize(exc.redirect))
		return (0);
	current = exc.redirect[i];
	while (current)
	{
		if (ft_strncmp(current, ">>", 2) == 0)
			status = ft_create_file(current + 2);
		else if (ft_strncmp(current, ">", 1) == 0)
			status = ft_create_file_trunc(current + 1);
		if (status == 1)
			return (status);
		current = exc.redirect[++i];
	}
	return (EXIT_SUCCESS);
}

void	ft_create_all_redirect(t_exc *exc, int size)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (!ret && i <= size)
	{
		ret = ft_create_redirect(exc[i]);
		i++;
	}
}
