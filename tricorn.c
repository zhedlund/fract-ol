/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:06:10 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/14 13:07:44 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int calculate_tricorn(double real, double imag)
{
    double  z_real = real;
    double  z_imag = imag;
    double  temp;
    int     i;
    
	i = 0;
    while (i < MAX_ITER)
    {
        if (z_real * z_real + z_imag * z_imag > 4.0)
            return (i); // diverged
        temp = z_real * z_real - z_imag * z_imag + real;
        z_imag = -2 * z_real * z_imag + imag;
        z_real = temp;
		i++;
    }
    return (MAX_ITER); // Did not diverge within max iterations
}

void render_tricorn(t_fractal *fractal)
{
    int i;
	double real;
	double imag;
    int y;
    int x;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom) + fractal->shift_x;
            imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom) + fractal->shift_y;
            i = calculate_tricorn(real, imag);
            fractal->color = pixel_color(i);
            ft_pixel_put(&fractal->img, x, y, fractal->color * i);
            x++;
        }
        y++;
    }
}