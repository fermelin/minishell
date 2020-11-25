# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 17:59:32 by fermelin          #+#    #+#              #
#    Updated: 2020/11/25 18:52:38 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC =	builtins_cd_export.c \
		builtins_unset_env_pwd.c \
		execve_test.c \
		error_handling.c \
		pipes.c \
		redirections.c \
		env_vars_utils.c \
		execution.c \
		parser/argv_parser.c \
		parser/command.c \
		parser/main.c \
		parser/utils_parser.c \
		struct_parser/p_lstall.c \
		struct_parser/p_lstnew.c
# 		parser.c \
# 		main.c \
# 		p_lists.c \

OBJ = $(SRC:.c=.o)

LIBFTDIR = ./libft/

LIBFT = $(LIBFTDIR)libft.a

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -I./libft
all:	$(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS)  $^ -o $(NAME) -Llibft -lft

$(LIBFT):
		make bonus -C $(LIBFTDIR)

clean:
		make clean -C $(LIBFTDIR)
		rm -f $(OBJ)
		rm -rf *.dSYM

fclean: clean
		make fclean -C $(LIBFTDIR)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

