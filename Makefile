# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 12:25:57 by zhedlund          #+#    #+#              #
#    Updated: 2024/08/20 16:22:30 by zhedlund         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
SRC = main.c initialization.c print_help_msg.c julia.c key_handler.c \
	mandelbrot.c render_fractal.c utils.c tricorn.c input_check.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re