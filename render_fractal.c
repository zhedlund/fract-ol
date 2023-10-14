/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:41:17 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/14 13:07:26 by zhedlund         ###   ########.fr       */
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

int render_fractal(t_fractal *fractal)
{
	if (fractal->win_ptr == NULL)
		return (1);
	double c_real = 0.355;
    double c_imag = 0.355; //adjust for julia set, struct member assign stdin
	render_julia(fractal, c_real, c_imag);
	//render_mandelbrot(fractal);
    //render_tricorn(fractal);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, fractal->img.mlx_img, 0, 0);
	return (0);
}