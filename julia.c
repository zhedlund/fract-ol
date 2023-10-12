/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:50:08 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/12 12:44:25 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int calculate_julia(double z_real, double z_imag, double c_real, double c_imag)
{
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
        z_imag = 2 * z_real * z_imag + c_imag;
        z_real = z_real_squared - z_imag_squared + c_real;
		i++;
    }
    return (MAX_ITER); // Did not diverge within max iterations
}

void render_julia(t_fractal *fractal, double c_real, double c_imag)
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
            // Map the pixel coordinates to the fractal coordinates
            real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom) + fractal->shift_x;
            imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom) + fractal->shift_y;
            i = calculate_julia(real, imag, c_real, c_imag);
            // Map the color to a pixel value based on the number of iterations
            fractal->color = pixel_color(i);
            ft_pixel_put(&fractal->img, x, y, fractal->color * i);
            x++;
        }
        y++;
    }
}
