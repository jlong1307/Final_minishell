NAME		=	minishell

#-------------------SOURCES PATH----------------------

LIBFT		=	./libft/
UTILS		=	./utils/
SOURCES		=	./srcs/
EXEC		=	./srcs/execute/
PARSING 	=	./parsing/
BUILTINS	=	./srcs/builtins/
ERRORS		=	./errors/

#-------------------COMPILATION----------------------

CC			=	gcc -g
FLAGS		=	-Wall -Werror -Wextra
READ = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
READ2 = -I/Users/$(USER)/.brew/opt/readline/include

#-------------------SOURCES FILES----------------------

SRCS		=	$(SOURCES)minishell.c \
				$(SOURCES)set_env_cpy.c \
				$(SOURCES)signal.c \
				$(EXEC)ft_execute_command.c \
				$(EXEC)ft_exec.c \
				$(SOURCES)ft_create_file.c \
				$(EXEC)ft_execute_pipe.c \
				$(SOURCES)ft_redirection.c \
				$(BUILTINS)ft_command.c \
				$(BUILTINS)ft_cd.c \
				$(BUILTINS)ft_export.c \
				$(BUILTINS)ft_export_utils.c \
				$(BUILTINS)ft_unset.c \
				$(BUILTINS)ft_cd_utils.c \
				$(SOURCES)ft_heredoc.c \
				$(SOURCES)ft_signal_heredoc.c \
				$(SOURCES)ft_init.c \
				$(BUILTINS)ft_exit.c \

SRCS_UTILS	=	$(UTILS)ft_tabsize.c \
				$(UTILS)ft_sort_string_tab.c \
				$(UTILS)ft_strchr_modified.c \
				$(UTILS)ft_strtrim_modified.c \
				$(UTILS)ft_strjoin_free.c \
				$(UTILS)create_cmd.c \
				$(UTILS)check_str_digit.c \
				$(UTILS)ft_get_last_file.c \
				$(UTILS)ft_free.c \

PARSG		=	$(PARSING)error_parsing.c \
				$(PARSING)find_command.c \
				$(PARSING)get_redirect.c \
				$(PARSING)parsing_untils.c \
				$(PARSING)parsing.c \
				$(PARSING)split_line.c \
				$(PARSING)split_parsing.c \
				$(PARSING)last_parsing.c \
				$(PARSING)parsing_var_env.c \
				$(PARSING)ft_join_free.c \
				$(PARSING)get_option.c \
				$(PARSING)get_arg.c \
				$(PARSING)get_heredoc.c \
				$(PARSING)last_parsing_bis.c \
				$(PARSING)check_error_synthax.c \

SRCS_ERRORS	=	$(ERRORS)check_builtin.c \
				$(ERRORS)ft_perror.c \
				$(ERRORS)ft_error_builtin.c \

#-------------------OBJECTS----------------------

OBJS		=	$(SRCS:.c=.o)

OBJS_PARS	= $(PARSG:.c=.o)

OBJS_UTILS	=	$(SRCS_UTILS:.c=.o)

OBJS_ERRORS	=	$(SRCS_ERRORS:.c=.o)


#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m


#-------------------RULES-----------------------
%.o: %.c
		@printf "$(YELLOW)Generating minishell objects... %-33.33s\r$(NO_COLOR)" $@
		@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(OBJS_PARS) $(OBJS_UTILS) $(OBJS_ERRORS)
			@echo "\n"
			@$(MAKE) -C $(LIBFT)
			@echo "$(GREEN)\nCompiling minishell...$(NO_COLOR)"
			@$(CC) $(FLAGS) $(READ) $(READ2) $(OBJS) $(OBJS_PARS) $(OBJS_UTILS) $(OBJS_ERRORS) -lreadline $(LIBFT)libft.a -o $(NAME)
			@echo "\nMinishell ready to be used!"

all:	$(NAME)

bonus:	$(NAME)

clean:
		@echo "$(RED)Deleting objects...\n$(NO_COLOR)"
		@$(MAKE) clean -C $(LIBFT)
	@rm -f $(OBJS) $(OBJS_PARS) $(OBJS_UTILS) $(OBJS_ERRORS)

fclean:	clean
		@echo "$(RED)Deleting executables...\n$(NO_COLOR)"
		@$(MAKE) fclean -C $(LIBFT)
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
