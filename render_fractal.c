/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:41:17 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/16 14:36:40 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void ft_pixel_put(t_img *img, int x, int y, int color)
{
    char *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

int pixel_color(int i)
{
    int r;
    int g;
    int b;

    // Map each iteration count to a color in the palette
    r = i % 252;
    g = i % 190;
    b = i % 17;
    return ((r << 16) | (g << 8) | b);
}
// FCBE11 (252, 190, 17) = british standard subtitle color

void    map(t_fractal *fractal, int x, int y, double *real, double *imag)
{
    *real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom) + fractal->shift_x;
    *imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom) + fractal->shift_y;
}

int render_fractal(t_fractal *fractal)
{
    if (fractal->name == 'j')
	    render_julia(fractal, fractal->julia_cx, fractal->julia_cy);
	else if (fractal->name == 'm')
        render_mandelbrot(fractal);
    else if (fractal->name == 't')
        render_tricorn(fractal);
    else
    {
        print_help_msg();
        exit(1);
    }
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, fractal->img.mlx_img, 0, 0);
	return (0);
}