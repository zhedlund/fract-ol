#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>
#include <complex.h>

#define WIDTH 800
#define HEIGHT 800

#define MLX_ERROR 1
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
    double shift_x;
    double shift_y;
    int     color;
}	t_fractal;

void ft_pixel_put(t_img *img, int x, int y, int color)
{
    char *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

/* Mandelbrot equation
 *		z = z^2 + c
 *		z is initially (0, 0)
 *		c is the constant/actual point
 *
 *		z = z^2 + c -> z1 = c + c
 *
 * 	Julia equation
 *		./fractol julia <real> <imag> 
 *		z = pixel point + constant
 *
 * real = (x^2 - y^2)
 * imag =  2*x*y
 */

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

int mandelbrot(double real, double imag)
{
    double z_real = 0;
    double z_imag = 0;
	double z_real_squared;
	double z_imag_squared;
    int i;
	
	i = 0;
    while (i < MAX_ITER)
    {
        z_real_squared = z_real * z_real;
        z_imag_squared = z_imag * z_imag;
        if (z_real_squared + z_imag_squared > 4.0) // 2^2 hypotenuse
            return (i); // diverged
        z_imag = 2 * z_real * z_imag + imag;
        z_real = z_real_squared - z_imag_squared + real;
		i++;
    }
    return (MAX_ITER); // Did not diverge within max iterations
}

// Function to render the Mandelbrot fractal
void render_mandelbrot(t_fractal *fractal)
{
    int i;
	double real;
	double imag;
    int y;
    int x;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // Map the pixel coordinates to the Mandelbrot coordinates
            real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom) + fractal->shift_x;
            imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom) + fractal->shift_y;
            i = mandelbrot(real, imag);
            fractal->color = pixel_color(i);
            ft_pixel_put(&fractal->img, x, y, fractal->color * i);
            x++;
        }
        y++;
    }
}

int julia(double z_real, double z_imag, double c_real, double c_imag)
{
	double z_real_squared;
	double z_imag_squared;
    int i;
	
	i = 0;
    while (i < MAX_ITER)
    {
        z_real_squared = z_real * z_real;
        z_imag_squared = z_imag * z_imag;
        if (z_real_squared + z_imag_squared > 4.0) // 2^2 hypotenuse
            return (i); // diverged
        z_imag = 2 * z_real * z_imag + c_imag;
        z_real = z_real_squared - z_imag_squared + c_real;
		i++;
    }
    return (MAX_ITER); // Did not diverge within max iterations
}


void render_julia(t_fractal *fractal, double c_real, double c_imag)
{
    int i;
	double real;
	double imag;
    int y;
    int x;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // Map the pixel coordinates to the fractal coordinates
            real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * fractal->zoom) + fractal->shift_x;
            imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * fractal->zoom) + fractal->shift_y;
            i = julia(real, imag, c_real, c_imag);
            // Map the color to a pixel value based on the number of iterations
            fractal->color = pixel_color(i);
            ft_pixel_put(&fractal->img, x, y, fractal->color * i);
            x++;
        }
        y++;
    }
}

int render(t_fractal *fractal)
{
	if (fractal->win_ptr == NULL)
		return (1);
	double c_real = 0.355;
    double c_imag = 0.355; //adjust for julia set
	render_julia(fractal, c_real, c_imag);
	//render_mandelbrot(fractal);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, fractal->img.mlx_img, 0, 0);
	return (0);
}

int close_window(void)
{
    exit(0); // Exit the program when called
}

int key_handler(int keycode, t_fractal *fractal)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		//fractal->win_ptr = NULL;
        exit(0);
	}
    if (keycode == XK_Left)
        fractal->shift_x += (0.1 * fractal->zoom);
    if (keycode == XK_Right)
        fractal->shift_x -= (0.1 * fractal->zoom);
    if (keycode == XK_Up)
        fractal->shift_y += (0.1 * fractal->zoom);
    if (keycode == XK_Down)
        fractal->shift_y -= (0.1 * fractal->zoom);
    return (0);
}

int mouse_handler(int button, int x, int y, t_fractal *fractal)
{
    (void)x;
    (void)y;

	if (button == Button4) // Mouse wheel up
		fractal->zoom *= 1.05; // Zoom in
	else if (button == Button5) // Mouse wheel down
		fractal->zoom *= 0.95; // Zoom out
	return (0);
}


int main(void)
{
	t_fractal fractal;
	
    fractal.zoom = 1.0; // Start with no zoom
	fractal.mlx_ptr = mlx_init();
	if (fractal.mlx_ptr == NULL)
		return (MLX_ERROR);
	fractal.win_ptr = mlx_new_window(fractal.mlx_ptr, WIDTH, HEIGHT, "Mandelbrot");
	if (fractal.win_ptr == NULL)
	{
		free(fractal.win_ptr);
		return (MLX_ERROR);
	}
    fractal.color = 0;
	//Setup hooks
	fractal.img.mlx_img = mlx_new_image(fractal.mlx_ptr, WIDTH, HEIGHT);
	fractal.img.addr = mlx_get_data_addr(fractal.img.mlx_img, &fractal.img.bpp,
			&fractal.img.line_len, &fractal.img.endian);
	mlx_loop_hook(fractal.mlx_ptr, &render, &fractal);
	mlx_hook(fractal.win_ptr, KeyPress, KeyPressMask, &key_handler, &fractal);
	mlx_hook(fractal.win_ptr, ButtonPress, ButtonPressMask, &mouse_handler, &fractal);
    mlx_hook(fractal.win_ptr, 17, 0, close_window, NULL);
	mlx_loop(fractal.mlx_ptr);
	// we will exit the loop if there's no window left, and execute this code
	mlx_destroy_image(fractal.mlx_ptr, fractal.img.mlx_img);
	mlx_destroy_display(fractal.mlx_ptr);
	free(fractal.mlx_ptr);
	return (0);
}