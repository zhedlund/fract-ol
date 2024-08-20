/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:02:42 by zhedlund          #+#    #+#             */
/*   Updated: 2024/08/20 16:21:10 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

# define WIDTH	800
# define HEIGHT	800
# define MAX_ITER 500

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	zoom;
	double	shift_x;
	double	shift_y;
	int		color;
	double	julia_cx;
	double	julia_cy;
	char	name;
}	t_fractal;

/* fractals */
int		calculate_julia(double z_real, double z_imag, double c_real,
			double c_imag);
int		calculate_mandelbrot(double real, double imag);
int		calculate_tricorn(double real, double imag);
void	fractal_init(t_fractal *fractal);
int		render_fractal(t_fractal *fractal);
void	render_julia(t_fractal *fractal, double c_real, double c_imag);
void	render_mandelbrot(t_fractal *fractal);
void	render_tricorn(t_fractal *fractal);

/* mlx related */
int		close_window(t_fractal *fractal);
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	hooks_init(t_fractal *fractal);
int		key_handler(int keycode, t_fractal *fractal);
int		mouse_handler(int button, int x, int y, t_fractal *fractal);

/* error handling */
int		input_check(t_fractal *fractal, int argc, char **argv);
void	print_control_options(void);
void	print_help_msg(void);

/* utils */
double	ft_atof(const char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(char c);
void	ft_putstr(char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);

#endif
