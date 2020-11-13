# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 17:59:32 by fermelin          #+#    #+#              #
#    Updated: 2020/11/13 17:59:35 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = main.c 

OBJ = $(SRC:.c=.o)

LIBFTDIR = ./libft/

LIBFT = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra 
all:	$(NAME)

%.o: %.c $(NAME) $(LIBFT)
		$(CC) $(CFLAGS) $< -o $@

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) -L$(LIBFTDIR) -lft $^ -o $(NAME)

$(LIBFT):
		make bonus -C $(LIBFTDIR)

clean:
		make clean -C $(LIBFTDIR)
		rm -f $(OBJ)

fclean: clean
		make fclean -C $(LIBFTDIR)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

