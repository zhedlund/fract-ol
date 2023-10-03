#include <mlx.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MAX_ITER 1000

typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
} t_data;

void ft_pixel_put(t_data *data, int x, int y, int color)
{
    char *pixel;

    pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)pixel = color;
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
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
            int color = mandelbrot(real, imag);

            // Color the pixel based on the number of iterations
            // For example, you can use a gradient color scheme
            int r = color % 100;
            int g = (color * 2) % 200;
            int b = (color * 3) % 100;

            int pixel_color = (r << 16) + (g << 8) + b;
            ft_pixel_put(img, x, y, pixel_color);
        }
    }
}

int main(void)
{
    t_data img;

    img.mlx = mlx_init();
    img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Mandelbrot Fractal");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);

    // Generate and draw the Mandelbrot fractal
    render_mandelbrot(&img);

    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);

    return (0);
}

