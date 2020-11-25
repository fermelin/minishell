# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 17:59:32 by fermelin          #+#    #+#              #
#    Updated: 2020/11/25 15:55:01 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC =	main.c \
		builtins_cd_export.c \
		builtins_unset_env_pwd.c \
		execve_test.c \
		error_handling.c \
		pipes.c \
		p_lists.c \
		redirections.c \
		parser.c \
		env_vars_utils.c

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

