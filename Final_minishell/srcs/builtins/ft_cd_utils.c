/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:23:32 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/20 14:59:58 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	set_pwd_and_oldpwd(char	*path, char *old_path, char ***env)
{
	char	*old_pwd;
	char	*pwd;
	int		index_old;
	int		index_pwd;

	index_old = find_var_in_env("OLDPWD", *env);
	index_pwd = find_var_in_env("PWD", *env);
	pwd = ft_strjoin("PWD=", path);
	old_pwd = ft_strjoin("OLDPWD=", old_path);
	if (index_pwd != -1)
	{
		free((*env)[index_pwd]);
		(*env)[index_pwd] = NULL;
		(*env)[index_pwd] = pwd;
	}
	if (index_old != -1)
	{
		free((*env)[index_old]);
		(*env)[index_old] = NULL;
		(*env)[index_old] = old_pwd;
	}
}

void	go_to_path(t_exc exc, char *old_path, char ***env)
{
	if (chdir(exc.arg[0]))
	{
		ft_perror("cd", exc.arg[0], strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(exc.arg[0], old_path, env);
}
