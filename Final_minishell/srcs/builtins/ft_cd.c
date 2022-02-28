/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:23:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/01 17:13:57 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

static void	go_to_final_path(char *arg, char ***env, char *old_path)
{
	char	*final_path;
	char	path[1024];
	char	*temp;

	getcwd(path, 1024);
	temp = ft_strjoin(path, "/");
	final_path = ft_strjoin(temp, arg);
	free (temp);
	temp = NULL;
	if (chdir(final_path))
	{
		ft_perror("cd", arg, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(final_path, old_path, env);
	free(final_path);
	final_path = NULL;
}

static void	go_path_from_home(char *arg, char *home, char ***env,
	char *old_path)
{
	char	*path_from_home;
	char	*temp;

	temp = ft_strtrim(ft_strdup(arg), "~");
	path_from_home = ft_strjoin(home, temp);
	free(temp);
	temp = NULL;
	if (chdir(path_from_home))
	{
		ft_perror("cd", path_from_home, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(path_from_home, old_path, env);
	free(path_from_home);
	path_from_home = NULL;
}

void	go_to_home(char ***env, char *old_path)
{
	char	*home;

	home = our_getenv(ft_strdup("HOME"), *env);
	if (chdir(home))
	{
		ft_perror("cd", home, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(home, old_path, env);
}

void	go_previous(char *arg, char *old_path, char ***env)
{
	char	path[1024];

	if (chdir("..") || !getcwd(path, 1024))
	{
		ft_perror("cd", arg, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(path, old_path, env);
}

int	ft_cd(t_exc exc, char ***env)
{
	char	old_path[1024];

	g_global.exit_code = 0;
	getcwd(old_path, 1024);
	if (exc.arg != NULL)
	{
		if (!ft_strncmp(exc.arg[0], "/", 1))
			go_to_path(exc, old_path, env);
		else if (!ft_strncmp(exc.arg[0], "..", 3))
			go_previous(exc.arg[0], old_path, env);
		else if (exc.arg[0][0] == '~' && !exc.arg[0][1])
			go_to_home(env, old_path);
		else if (exc.arg[0][0] == '~' && exc.arg[0][1] == '/')
			go_path_from_home(exc.arg[0], getenv("HOME"), env, old_path);
		else
			go_to_final_path(exc.arg[0], env, old_path);
	}
	else
		go_to_home(env, old_path);
	return (CD);
}
