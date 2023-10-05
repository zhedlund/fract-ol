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
#define MAX_ITER 100

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	zoom;
    double shift_x;
    double shift_y;
}	t_data;

void ft_pixel_put(t_img *img, int x, int y, int color)
{
    char *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

/*void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		// big endian, MSB is the leftmost bit
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		//little endian, LSB is the leftmost bit
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}*/

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
        if (z_real_squared + z_imag_squared > 4.0)
            return (i); // diverged
        z_imag = 2 * z_real * z_imag + imag;
        z_real = z_real_squared - z_imag_squared + real;
		i++;
    }
    return (MAX_ITER); // Did not diverge within max iterations
}

// Function to calculate the Mandelbrot set
/*int mandelbrot(double real, double imag)
{
    double complex z = real + imag * I;
    double complex c = z;

    for (int n = 0; n < MAX_ITER; ++n)
    {
        if (cabs(z) > 2.0)
            return n; // Diverged

        z = z * z + c; // Mandelbrot iteration formula
    }

    return (MAX_ITER); // Did not diverge within the maximum iterations
} */

// Function to render the Mandelbrot fractal
void render_mandelbrot(t_data *data)
{
    int fractal;
    int pixel_color;
	double real;
	double imag;

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            // Map the pixel coordinates to the Mandelbrot coordinates
            real = (x - WIDTH / 2.0) * 4.0 / (WIDTH * data->zoom) + data->shift_x;
            imag = (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * data->zoom) + data->shift_y;

            fractal = mandelbrot(real, imag);

            // Map the color to a pixel value based on the number of iterations
            int r = (fractal * 10) % 50;
            int g = (fractal * 10) % 200;
            int b = (fractal * 10) % 235;

            pixel_color = (r << 16) + (g << 8) + b;
            ft_pixel_put(&data->img, x, y, pixel_color);
        }
    }
}

int close_window(void *param)
{
    exit(0); // Exit the program when called
}

int key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		//data->win_ptr = NULL;
        exit(0);
	}
    if (keycode == XK_Left)
        data->shift_x += (0.1 * data->zoom);
    if (keycode == XK_Right)
        data->shift_x -= (0.1 * data->zoom);
    if (keycode == XK_Up)
        data->shift_y += (0.1 * data->zoom);
    if (keycode == XK_Down)
        data->shift_y -= (0.1 * data->zoom);
	return (0);
}

int mouse_handler(int button, int x, int y, t_data *data)
{
	if (button == Button4) // Mouse wheel up
		data->zoom *= 1.05; // Zoom in
	else if (button == Button5) // Mouse wheel down
		data->zoom *= 0.95; // Zoom out
	return (0);
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_mandelbrot(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(void)
{
	t_data data;
	
    data.zoom = 1.0; // Start with no zoom
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Mandelbrot");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	/* Setup hooks */
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &key_handler, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &mouse_handler, &data);
    mlx_hook(data.win_ptr, 17, 0, close_window, NULL);
	mlx_loop(data.mlx_ptr);
	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}