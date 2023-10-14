/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:39:40 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/14 13:06:56 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    print_control_options(void)
{
    ft_putstr("===== Program controls =====\n");
    ft_putstr("Arrow keys to move view\n");
    ft_putstr("Mouse wheel to zoom in/out\n");
    ft_putstr("ESC or close window to end program\n");
}


void    print_help_msg(void)
{
    ft_putstr("\n====== FRACT-OL ======\n");
    ft_putstr("Choose a fractal:\n");
    ft_putstr("\tm - Mandelbrot\n");
    ft_putstr("\tj - Julia\n");
    ft_putstr("For Julia you may specify starting values,\n");
    ft_putstr("to get different shapes\n");
    ft_putstr("The values should be between -2.0-2.0\n");
    ft_putstr("Usage example: ./fractol j 0.355, 0.355\n\n");
    ft_putstr("======== Colors ========\n");
    ft_putstr("To choose a color, input hexadecimal code\n");
    ft_putstr("Usage example: ./fractol j 0.355 0.355 00FF80\n\n");
    print_control_options();
}