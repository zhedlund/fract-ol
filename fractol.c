/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:34:00 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/11 16:55:35 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    hooks_init(t_fractal *fractal)
{
    mlx_hook(fractal->win_ptr, KeyPress, KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->win_ptr, ButtonPress, ButtonPressMask, mouse_handler, fractal);
    mlx_hook(fractal->win_ptr, 17, 0, close_window, NULL);
}

void    fractal_init(t_fractal *fractal)
{
	fractal->mlx_ptr = mlx_init();
	if (fractal->mlx_ptr == NULL)
		exit(1);
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, WIDTH, HEIGHT, "Fract-ol");
	if (fractal->win_ptr == NULL)
	{
		free(fractal->win_ptr);
		exit(1);
	}
    fractal->shift_x = 0.0;
    fractal->shift_y = 0.0;
    fractal->zoom = 1.0; // Start with no zoom
    fractal->color = 0xFCBE11;
	/* Setup hooks */
	fractal->img.mlx_img = mlx_new_image(fractal->mlx_ptr, WIDTH, HEIGHT);
	fractal->img.addr = mlx_get_data_addr(fractal->img.mlx_img,
            &fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
}

int main(int argc, char **argv)
{
    t_fractal   fractal;
    
    if (argc < 2)
        print_help_msg();
        exit(0);
    input_check(&fractal, argc, argv); // not done
    fractal_init(&fractal); 
    hooks_init(&fractal); 
    render_fractal(&fractal); 
    print_control_options(); 
    mlx_loop_hook(fractal.mlx_ptr, &render_fractal, &fractal);
	mlx_loop(fractal.mlx_ptr);
	/* exit loop if no window left & execute code: */
	mlx_destroy_image(fractal.mlx_ptr, fractal.img.mlx_img);
	mlx_destroy_display(fractal.mlx_ptr);
	free(fractal.mlx_ptr);
	return (0);
}