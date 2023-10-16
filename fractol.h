/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:02:42 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/16 14:14:57 by zhedlund         ###   ########.fr       */
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
    double	shift_x;
    double	shift_y;
    int     color;
	double	julia_cx;
	double	julia_cy;
	char	name;
}	t_fractal;

/* fractals */
int     calculate_julia(double z_real, double z_imag, double c_real, double c_imag);
int     calculate_mandelbrot(double real, double imag);
int		calculate_tricorn(double real, double imag);
void    render_julia(t_fractal *fractal, double c_real, double c_imag);
void    render_mandelbrot(t_fractal *fractal);
void	render_tricorn(t_fractal *fractal);

/* rendering utils */
int     pixel_color(int i);
void    ft_pixel_put(t_img *img, int x, int y, int color);
int     render_fractal(t_fractal *fractal);

/* mlx stuff */
int		key_handler(int keycode, t_fractal *fractal);
int     mouse_handler(int button, int x, int y, t_fractal *fractal);
void    hooks_init(t_fractal *fractal);
int     close_window(t_fractal *fractal);

/* stdout */
void    print_control_options(void);
void    print_help_msg(void);
int		input_check(t_fractal *fractal, int argc, char **argv);
void	clean_exit(int exit_code, t_fractal *fractal);

/* utils */
void	ft_putstr(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
double	ft_atof(const char *str);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(char c);
void	ft_putstr(char *str);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
