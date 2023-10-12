# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 12:25:57 by zhedlund          #+#    #+#              #
#    Updated: 2023/10/12 13:20:00 by zhedlund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -lmlx -lXext -lX11 -lm -Wall -Wextra -Werror -g
SRC = fractol.c help_msg.c julia.c key_handler.c mandelbrot.c render_fractal.c utils.c \
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		@rm -rf $(OBJ)

fclean:	clean
		@rm -f $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re