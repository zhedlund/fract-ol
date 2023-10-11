# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

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

#define WIDTH 800
#define HEIGHT 800
#define MAX_ITER 1000
#define MLX_ERROR 1

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win;
	t_img	img;
	double	zoom;
	double	offset_x;
	double	offset_y;
}	t_data;

void ft_pixel_put(t_data *data, int x, int y, int color)
{
    char *pixel;

    pixel = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
    *(unsigned int *)pixel = color;
}

int close_window(void *param)
{
    exit(0); // Exit the program when called
}

int key_hook(int key_code, void *param)
{
    if (key_code == XK_Escape) // XK_Escape is keycode for ESC
        exit(0); // Exit the program
    return (0);
}


int mandelbrot(double real, double imag)
{
    double z_real = 0;
    double z_imag = 0;
    int i;
	double	escape_value; // hypotenuse
	
    for (i = 0; i < MAX_ITER; i++)
    {
        double z_real_squared = z_real * z_real;
        double z_imag_squared = z_imag * z_imag;
        if (z_real_squared + z_imag_squared > 4.0)
            return i;
        z_imag = 2 * z_real * z_imag + imag;
        z_real = z_real_squared - z_imag_squared + real;
    }
    return MAX_ITER;
}

void render_mandelbrot(t_data *img)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
            int color = mandelbrot(real, imag);

            // Color the pixel based on the number of iterations
            int r = (color * 10) % 50;
            int g = (color * 10) % 200;
            int b = (color * 10) % 235;

            int pixel_color = (r << 16) + (g << 8) + b;
            ft_pixel_put(img, x, y, pixel_color);
        }
    }
}

int render(t_data *data)
{
	if (data->win == NULL)
		return (1);

	render_mandelbrot(data);

	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.mlx_img, 0, 0);

	return (0);
}


/*int mouse_handler(int button, int x, int y, t_data *img)
{
    if (button == Button5) // Mouse wheel up (zoom in)
    {
        // Adjust the zoom level (e.g., multiply by a factor < 1)
        img->zoom *= 0.95; // Adjust the factor as needed
        // refresh rendering with updated zoom level
        render_mandelbrot(img);
    }
    else if (button == Button4) // Mouse wheel down (zoom out)
    {
        // Adjust the zoom level (e.g., multiply by a factor > 1)
        img->zoom *= 1.05; // Adjust the factor as needed
        // refresh rendering with updated zoom level
        render_mandelbrot(img);
    }
    return (0);
}*/

int mouse_handler(int button, int x, int y, t_data *data)
{
	if (button == 4) // Mouse wheel up
	{
		data->zoom *= 1.05; // Zoom in
	}
	else if (button == 5) // Mouse wheel down
	{
		data->zoom *= 0.95; // Zoom out
	}

	// Ensure zoom stays within reasonable limits
	/*if (data->zoom < 0.1)
	{
		data->zoom = 0.1;
	}
	else if (data->zoom > 10)
	{
		data->zoom = 10;
	}*/
    render(data); // Refresh rendering with updated zoom level
	return (0);
}

int main(void)
{
    t_data  data;
    data.zoom = 1.0;
    data.zoom = 1.0;
	data.offset_x = 0.0;
	data.offset_y = 0.0;

    data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Mandelbrot Set");
	if (data.win == NULL)
	{
		free(data.win);
		return (MLX_ERROR);
	}

	/* Setup hooks */
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);

	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
    
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_hook, &data);

	mlx_hook(data.win, ButtonPress, ButtonPressMask, &mouse_handler, &data);
    
    // Register the close_window function to be called when the window is closed
    mlx_hook(data.win, 17, 0, close_window, NULL);
    mlx_key_hook(data.win, key_hook, 0);
	
    mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);

	return (0);
}

