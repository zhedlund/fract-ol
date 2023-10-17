/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:39:40 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/17 20:52:49 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_control_options(void)
{
	ft_putstr("\n\t============ Program controls =============\n\n");
	ft_putstr("\t- Arrow keys to move view\n");
	ft_putstr("\t- Mouse wheel to zoom in/out\n");
	ft_putstr("\t- Change color by pressing keys 1, 2, 3\n");
	ft_putstr("\t- ESC or close window to end program\n\n");
	ft_putstr("\t===========================================\n\n");
}

void	print_help_msg(void)
{
	ft_putstr("\n\t================ FRACT-OL =================\n\n");
	ft_putstr("\tChoose a fractal:\n\n");
	ft_putstr("\t\tm - Mandelbrot\n");
	ft_putstr("\t\tj - Julia\n");
	ft_putstr("\t\tt - Tricorn\n\n");
	ft_putstr("\t- For Julia you can specify starting values,\n");
	ft_putstr("\t  to get different shapes\n");
	ft_putstr("\t- The values should be between -2.0-2.0\n\n");
	ft_putstr("\t- Usage example: ./fractol m\n");
	ft_putstr("\t\t\t ./fractol j 0.35 0.5\n\n");
	print_control_options();
}
