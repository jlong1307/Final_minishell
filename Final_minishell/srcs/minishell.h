/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:44:37 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/01 17:47:39 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/libft.h" 
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define LONG_MIN_CHAR "-9223372036854775808"
# define LONG_MAX_CHAR "9223372036854775807"

typedef struct s_global
{
	pid_t	fork_pid;
	int		exit_code;
	int		in_heredoc;
}	t_global;

typedef struct s_exc
{
	char	*cmd;
	char	*opt;
	char	**arg;
	char	**input;
	char	**output;
	char	**heredoc;
	char	**redirect;
	char	**env_cpy;
	int		regroup_exit;
}				t_exc;

/*structure pour le parsin qui sera free
*quand le tableau de t_exc sera parfait
*	char	**input;
	char	**output;
*/
typedef struct s_pars
{
	int		pipe;
	char	*command;
	char	**option;
	char	**arg;
	char	**redirect;
	char	**heredoc;
	char	*next_char;
	int		regroup_exit;
}				t_pars;

typedef struct s_state
{
	char	*line;
	int		eof;
	int		n_of_pipe;
	int		*pipe;
	char	**cm;

}				t_state;

typedef struct s_tmp
{
	char	*tmp;
	char	*rest;
	char	*new_line;
	int		n;
	int		m;
	char	*nl;
	char	*var;
}				t_tmp;

typedef struct s_quote
{
	int	simple_quote;
	int	double_quote;
}				t_quote;

typedef struct s_exp_list
{
	char				*line;
	struct s_exp_list	*next;
}	t_exp_list;

/*=========UTILS=========*/

int			ft_tabsize(char **tab);
int			ft_atoi_modified(const char *s);
int			ft_strchr_modified(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			size_list(t_exp_list *stack);
int			check_str_digit(char *str);
char		*ft_strtrim_modified(char *s1, char const *set);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_get_last_input(t_exc cmd);
char		*ft_get_last_output(t_exc cmd);
void		ft_sort_string_tab(char **tab);
void		ft_free_tab_exc(t_exc *last_tab, t_pars *tab);
char		*ft_strtrim_plus_equal(char *arg);
char		**create_cmd(t_exc command);
t_exp_list	*add_front(t_exp_list *stack, char *str);
t_exp_list	*add_back(t_exp_list *stack, char *str);
t_exp_list	*remove_back(t_exp_list *stack);
t_exp_list	*remove_front(t_exp_list *stack);
t_exp_list	*freelist(t_exp_list *stack);
int			ft_check_exist(char *cmd);

/*=========SRCS=========*/

int			ft_execute_command(t_exc cmd, char ***env, int nbr_pipe);
int			execute(t_exc exc, char ***env, int nbr_pipe);
void		ft_create_all_redirect(t_exc *exc, int size);
long		get_lvl_shlvl(char ***env);
char		**cpy_env(char **env);
void		update_shlvl(char ***env);
void		ft_execute_pipe(t_exc *cmds, int nbr_pipe, char ***env, int *fds);
void		ft_redirect_input(t_exc cmd, int n_pipe, int *fds);
void		ft_redirect_output(t_exc cmd, int n_pipe, int *fds, int nbr_pipe);
int			ft_heredoc(t_exc cmd);
void		init_struct(t_state *state);
void		init_variables(t_state **state, t_pars **tab, t_exc **exc);
void		ft_exec_heredoc(int nbr_pipe, t_exc *cmds);
void		ft_open_pipes(int nbr_pipe, int **fds);
void		ft_set_stdin_back(int fd_in);
void		ft_close_pipes(int nbr_pipe, int *fds);
char		*our_getenv_bis(char *line, char **env);
/*=========PARSING=========*/

t_pars		*parsing(t_state *s, char **env);
int			check_parsing(t_state *s);
t_pars		*split_line(t_state *line, char **env);
t_pars		*find_command(t_state *s, char **env);
int			ft_get_index(char *s);
void		init_tmp(t_tmp *tmp);
int			ft_check_space(char *line);
int			check_redirection(char *line);
int			check_quote(char *line, int index);
int			*get_index(char *line, size_t size, char c);
int			*get_index(char *line, size_t size, char c);
void		init_tab(t_pars *tab);
void		ft_free_pars_tab(t_state *s);
void		ft_free_pars_error(t_state *s);
char		*our_getenv(char *line, char **env);
char		**ft_split_parsing(char *s, char c);
char		*get_redirect(char *line, t_pars *tab_here);
char		**ft_arg(char **arg, char **env);
t_exc		*last_parsing(t_pars *tab, char **env);
char		*ft_strjoin_double_free(char *s1, char *s2);
char		**get_opt(char *line, int n, char **env);
int			check_is_opt(char *line);
char		**ft_echo_option(int n);
void		ft_echo_arg(char *line, char **env, t_pars *tab);
void		get_arg(char *line, char *cmd, char **env, t_pars *tab);
char		*get_heredoc(char *line, t_pars *tab_here);
void		split_pipe(t_state *s);
void		ft_error_malloc(t_state *s);
void		init_ptn(t_exc *tab);
char		*check_var_env(char *line, char **env);
char		*get_var_env_bis(char *tab_redirect, char **env, int i);
char		*ft_arg_bis(char *arg, char **env);
char		*check_all_string(char	*line, char **env);
int			check_opt_is_valid(char	*line);
void		check_all_string_bis_bis(char *line, t_tmp *tmp, char c, int index);
int			return_index_all_string(char *line, int index, char c);
int			ft_check_char_syntax(t_state *s, char c, int i);
int			ft_check_command(char *line);

/*=========ERROR=========*/

int			check_builtin(char *cmd);
void		ft_perror(char *cmd, char *arg, char *err_msg);
int			ft_check_error_arg_opt(t_exc exc);
int			ft_error_pipe(void);

/*=========BUILTIN=========*/

int			ft_echo(t_exc exc);
int			ft_env(char **env);
int			ft_pwd(void);
int			ft_cd(t_exc exc, char ***env);
int			ft_export(t_exc exc, char ***env);
int			ft_unset(t_exc exc, char ***env);
void		ft_exit(t_exc exc, int nbr_pipe);
void		create_new_var_env(char *arg, char ***env);
void		modify_var_in_env(char *arg, char ***env);
int			find_var_in_env(char *arg, char **env);
int			check_if_already_in_env(char *arg, char ***env);
char		**cpy_env(char **env);
char		**ft_realloc_env(char ***env, int size);
void		set_pwd_and_oldpwd(char	*path, char *old_path, char ***env);
void		go_to_path(t_exc exc, char *old_path, char ***env);

/*=========READLINE=========*/

void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);

/*==========SIGNAL==========*/
void		ft_signal_msg(void);
void		ft_ctrl_c(int signal);
void		ft_ctrl_backslash(int signal);
void		ft_set_signal(void);
void		ft_ctrl_d(t_state *state);
void		ft_signal(void);
#endif
