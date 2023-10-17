/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:06:10 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/17 20:27:41 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_tricorn(double real, double imag)
{
	double	z_real;
	double	z_imag;
	double	temp;
	int		i;

	z_real = real;
	z_imag = imag;
	i = 0;
	while (i < MAX_ITER)
	{
		if (z_real * z_real + z_imag * z_imag > 4.0)
			return (i);
		temp = z_real * z_real - z_imag * z_imag + real;
		z_imag = -2 * z_real * z_imag + imag;
		z_real = temp;
		i++;
	}
	return (0);
}

void	render_tricorn(t_fractal *fractal)
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
			iter = calculate_tricorn(real, imag);
			ft_pixel_put(&fractal->img, x, y, fractal->color * iter);
			x++;
		}
		y++;
	}
}
