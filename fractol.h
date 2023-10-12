/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:02:42 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/12 13:52:12 by zhedlund         ###   ########.fr       */
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
#define MAX_ITER 500

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

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	zoom;
    double shift_x;
    double shift_y;
    int     color;
}	t_fractal;

/* fractals */
int     calculate_julia(double z_real, double z_imag, double c_real, double c_imag);
int     calculate_mandelbrot(double real, double imag);
void    render_julia(t_fractal *fractal, double c_real, double c_imag);
void    render_mandelbrot(t_fractal *fractal);

/* rendering utils */
int     pixel_color(int i);
void    ft_pixel_put(t_img *img, int x, int y, int color);
int     render_fractal(t_fractal *fractal);

/* mlx stuff */
int		key_handler(int keycode, t_fractal *fractal);
int     mouse_handler(int button, int x, int y, t_fractal *fractal);
void    hooks_init(t_fractal *fractal);
int     close_window(void);

/* stdout */
void    print_control_options(void);
void    print_help_msg(void);

/* utils */
void	ft_putstr(char *str);

#endif
