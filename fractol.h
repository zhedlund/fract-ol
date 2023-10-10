/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:02:42 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/10 15:40:49 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

#define HELP_MSG "Please enter "./fractol mandelbrot\" or "./fractol julia <value1> <value2>\""

#define WIDTH	800
#define	HEIGHT	800

//Basic colors
#define BLACK				0x000000  // RGB(0, 0, 0)
#define WHITE				0xFFFFFF  // RGB(255, 255, 255)
#define RED					0xFF0000  // RGB(255, 0, 0)
#define GREEN				0x00FF00  // RGB(0, 255, 0)
#define BLUE				0x0000FF  // RGB(0, 0, 255)

//vibrant colors
#define MAGENTA_BURST		0xFF00FF
#define LIME_SHOCK			0xCCFF00
#define NEON_ORANGE			0xFF6600
#define PSYCHEDELIC_PURPLE	0x660066
#define AQUA_DREAM			0x33CCCC
#define HOT_PINK			0xFF66B2
#define ELECTRIC_BLUE		0x0066FF
#define LAVA_RED			0xFF3300

#endif
