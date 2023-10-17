/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:41:51 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/17 20:48:49 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.mlx_img);
	mlx_destroy_display(fractal->mlx_ptr);
	free(fractal->mlx_ptr);
	exit(0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double	real;
	double	imag;

	real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom)
		+ fractal->shift_x;
	imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom)
		+ fractal->shift_y;
	if (button == Button4)
	{
		fractal->zoom *= 1.05;
		fractal->shift_x = real - (x - WIDTH / 2.0) * 4.0
			/ (WIDTH * fractal->zoom);
		fractal->shift_y = imag - (y - HEIGHT / 2.0) * 4.0
			/ (HEIGHT * fractal->zoom);
	}
	else if (button == Button5)
	{
		fractal->zoom *= 0.95;
		fractal->shift_x = real - (x - WIDTH / 2.0) * 4.0
			/ (WIDTH * fractal->zoom);
		fractal->shift_y = imag - (y - HEIGHT / 2.0) * 4.0
			/ (HEIGHT * fractal->zoom);
	}
	return (0);
}

int	key_handler(int keycode, t_fractal *fractal)
{
	if (keycode == XK_Escape)
		close_window(fractal);
	if (keycode == XK_Left)
		fractal->shift_x += (0.1 * fractal->zoom);
	if (keycode == XK_Right)
		fractal->shift_x -= (0.1 * fractal->zoom);
	if (keycode == XK_Up)
		fractal->shift_y += (0.1 * fractal->zoom);
	if (keycode == XK_Down)
		fractal->shift_y -= (0.1 * fractal->zoom);
	if (keycode == XK_1)
		fractal->color = 0x001050;
	if (keycode == XK_2)
		fractal->color = 0x620060;
	if (keycode == XK_3)
		fractal->color = 0x800080;
	render_fractal(fractal);
	return (0);
}
