# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 12:25:57 by zhedlund          #+#    #+#              #
#    Updated: 2023/10/09 16:21:25 by zhedlund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -lmlx -lXext -lX11 -lm

SRC =                     

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf *.o

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re