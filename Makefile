# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 17:59:32 by fermelin          #+#    #+#              #
#    Updated: 2021/01/11 14:32:56 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/builtins/builtins_cd.c \
		src/builtins/builtins_export.c \
		src/builtins/builtins_export_utils.c \
		src/builtins/builtins_utils.c \
		src/builtins/builtins_unset_env_pwd.c \
		src/builtins/exec_child_process.c \
		src/builtins/error_handling.c \
		src/builtins/pipes.c \
		src/builtins/redirections.c \
		src/builtins/env_vars_utils.c \
		src/builtins/execution.c \
		src/builtins/builtins_echo_exit.c \
		src/parser/command.c \
		src/parser/main.c \
		src/parser/utils_syntax.c \
		src/parser/filling_token_struct.c \
		src/parser/list_struct.c \
		src/parser/utils_variable.c \
		src/parser/help_functions.c \
		src/parser/split_args_and_redirects.c \
		src/parser/check_syntax_errors.c \
		src/parser/parser.c 

OBJ = $(SRC:.c=.o)

LIBFTDIR = ./libft/

LIBFT = $(LIBFTDIR)libft.a

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -I./libft -I./includes #-fsanitize=address

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
