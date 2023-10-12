/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:50:42 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/11 15:58:45 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int calculate_mandelbrot(double real, double imag)
{
    double z_real = 0;
    double z_imag = 0;
	double z_real_squared;
	double z_imag_squared;
    int i;
	
	i = 0;
    while (i < MAX_ITER)
    {
        z_real_squared = z_real * z_real;
        z_imag_squared = z_imag * z_imag;
        if (z_real_squared + z_imag_squared > 4.0) // 2^2 hypotenuse
            return (i); // diverged
        z_imag = 2 * z_real * z_imag + imag;
        z_real = z_real_squared - z_imag_squared + real;
		i++;
    }
    return (MAX_ITER); // Did not diverge within max iterations
}

// Function to render the Mandelbrot fractal
void render_mandelbrot(t_fractal *fractal)
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
            // Map the pixel coordinates to the Mandelbrot coordinates
            real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom) + fractal->shift_x;
            imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom) + fractal->shift_y;
            i = calculate_mandelbrot(real, imag);
            fractal->color = pixel_color(i);
            ft_pixel_put(&fractal->img, x, y, fractal->color * i);
            x++;
        }
        y++;
    }
}