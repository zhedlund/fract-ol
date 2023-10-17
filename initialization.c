/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:50:30 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/17 19:13:44 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	hooks_init(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr, KeyPress, KeyPressMask, key_handler,
		fractal);
	mlx_hook(fractal->win_ptr, ButtonPress, ButtonPressMask, mouse_handler,
		fractal);
	mlx_hook(fractal->win_ptr, 17, 0, close_window, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_ptr = mlx_init();
	if (fractal->mlx_ptr == NULL)
		exit(1);
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, WIDTH, HEIGHT,
			"Fract-ol");
	if (fractal->win_ptr == NULL)
	{
		free(fractal->win_ptr);
		exit(1);
	}
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->color = 0x800080;
	fractal->img.mlx_img = mlx_new_image(fractal->mlx_ptr, WIDTH, HEIGHT);
	fractal->img.addr = mlx_get_data_addr(fractal->img.mlx_img,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
}
