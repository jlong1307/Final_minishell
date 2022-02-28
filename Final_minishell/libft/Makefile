# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 10:07:20 by jvander-          #+#    #+#              #
#    Updated: 2022/01/12 12:05:45 by jvander-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

SRC		=	ft_isdigit.c \
			ft_putendl_fd.c \
			ft_strjoin.c \
			ft_substr.c \
			ft_isalnum.c \
			ft_isprint.c \
			ft_putnbr_fd.c \
			ft_strlen.c \
			ft_tolower.c \
			ft_isalpha.c \
			ft_itoa.c \
			ft_putstr_fd.c \
			ft_strmapi.c \
			ft_toupper.c \
			ft_isascii.c \
			ft_putchar_fd.c \
			ft_split.c \
			ft_strtrim.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strchr.c \
			ft_strcat.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_putstr.c \
			ft_putchar.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_atol.c \

#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m

#-------------------RULES-----------------------
%.o: %.c
	@printf "$(YELLOW)Generating libft objects... %-33.33s\r$(NO_COLOR)" $@
	@$(CC) $(FLAGS) -o $@ -c $?

OBJ		=	$(SRC:%.c=%.o)

all:	$(NAME)

$(NAME): $(OBJ)
		@echo "\n\n$(GREEN)Compiling libft...$(NO_COLOR)"
		@ar -rcs $(NAME) $(OBJ)

clean:
		@rm -f $(OBJ)

fclean:	clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
