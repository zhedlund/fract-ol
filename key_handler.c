/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:41:51 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/14 13:07:06 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_window(void)
{
    exit(0); // Exit the program when called
}

int mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	
	if (button == Button4) // Mouse wheel up
		fractal->zoom *= 1.05; // Zoom in
	else if (button == Button5) // Mouse wheel down
		fractal->zoom *= 0.95; // Zoom out
	return (0);
}

int key_handler(int keycode, t_fractal *fractal)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		//fractal->win_ptr = NULL;
       	exit(0);
	}
	if (keycode == XK_Left)
		fractal->shift_x += (0.1 * fractal->zoom);
    if (keycode == XK_Right)
		fractal->shift_x -= (0.1 * fractal->zoom);
    if (keycode == XK_Up)
		fractal->shift_y += (0.1 * fractal->zoom);
	if (keycode == XK_Down)
		fractal->shift_y -= (0.1 * fractal->zoom);
	return (0);
}