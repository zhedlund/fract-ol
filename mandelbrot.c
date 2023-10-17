/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:50:42 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/17 20:19:42 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_mandelbrot(double real, double imag)
{
	double	z_real;
	double	z_imag;
	double	z_real_squared;
	double	z_imag_squared;
	int		i;

	z_real = 0;
	z_imag = 0;
	i = 0;
	while (i < MAX_ITER)
	{
		z_real_squared = z_real * z_real;
		z_imag_squared = z_imag * z_imag;
		if (z_real_squared + z_imag_squared > 4.0)
			return (i);
		z_imag = 2 * z_real * z_imag + imag;
		z_real = z_real_squared - z_imag_squared + real;
		i++;
	}
	return (0);
}

void	render_mandelbrot(t_fractal *fractal)
{
	int		iter;
	double	real;
	double	imag;
	int		y;
	int		x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom)
				+ fractal->shift_x;
			imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom)
				+ fractal->shift_y;
			iter = calculate_mandelbrot(real, imag);
			ft_pixel_put(&fractal->img, x, y, fractal->color * iter);
			x++;
		}
		y++;
	}
}
