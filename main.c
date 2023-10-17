/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:34:00 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/17 20:14:24 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (argc < 2)
	{
		print_help_msg();
		return (0);
	}
	input_check(&fractal, argc, argv);
	fractal_init(&fractal);
	hooks_init(&fractal); 
	render_fractal(&fractal); 
	print_control_options(); 
	mlx_loop_hook(fractal.mlx_ptr, &render_fractal, &fractal);
	mlx_loop(fractal.mlx_ptr);
	return (0);
}
