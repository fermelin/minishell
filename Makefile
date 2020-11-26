# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 17:59:32 by fermelin          #+#    #+#              #
#    Updated: 2020/11/26 17:50:06 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC =	src/builtins_cd_export.c \
		src/builtins_unset_env_pwd.c \
		src/execve_test.c \
		src/error_handling.c \
		src/pipes.c \
		src/redirections.c \
		src/env_vars_utils.c \
		src/execution.c \
		parser/command.c \
		parser/main.c \
		parser/utils_parser.c \
		struct_parser/p_lstall.c \
		struct_parser/p_lstnew.c \
		trash/parser.c 
# 		trash/main.c \
# 		trash/p_lists.c \

OBJ = $(SRC:.c=.o)

LIBFTDIR = ./libft/

LIBFT = $(LIBFTDIR)libft.a

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -I./libft -I./includes #-D ANTON=1

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

