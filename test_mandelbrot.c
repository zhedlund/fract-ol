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

typedef struct s_data
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    double  zoom;
} t_data;

void ft_pixel_put(t_data *data, int x, int y, int color)
{
    char *pixel;

    pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
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
    double zoom = img->zoom; //get current zoom level

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

int mouse_handler(int button, int x, int y, t_data *img)
{
    if (button == 5) // Mouse wheel up (zoom in)
    {
        // Adjust the zoom level (e.g., multiply by a factor < 1)
        img->zoom *= 0.95; // Adjust the factor as needed
        // refresh rendering with updated zoom level
        render_mandelbrot(img);
    }
    else if (button == 4) // Mouse wheel down (zoom out)
    {
        // Adjust the zoom level (e.g., multiply by a factor > 1)
        img->zoom *= 1.05; // Adjust the factor as needed
        // refresh rendering with updated zoom level
        render_mandelbrot(img);
    }
    return (0);
}

int main(void)
{
    t_data  img;
    img.zoom = 1.0;

    img.mlx = mlx_init();
    img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Mandelbrot Fractal");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);

    // Generate and render the Mandelbrot fractal
    render_mandelbrot(&img);

    // Register the close_window function to be called when window is closed
    //17="DestroyNotify" event, close window when clicking "X" button
    mlx_hook(img.win, 17, 0, close_window, NULL); 

    // Register the key_hook function to handle key events
    mlx_key_hook(img.win, key_hook, NULL);

    // register mouse_hook to zoom with mouseweel, 5=up, 4=down
    mlx_hook(img.win, 5, 0, mouse_handler, &img);
    mlx_hook(img.win, 4, 0, mouse_handler, &img);

    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);

    return (0);
}

