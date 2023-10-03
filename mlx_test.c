#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500

#define MLX_ERROR 1

//Basic colors
#define BLACK				0x000000  // RGB(0, 0, 0)
#define WHITE				0xFFFFFF  // RGB(255, 255, 255)
#define RED					0xFF0000  // RGB(255, 0, 0)
#define GREEN				0x00FF00  // RGB(0, 255, 0)
#define BLUE				0x0000FF  // RGB(0, 0, 255)

//cc file.c -lmlx -lXext -lX11 -lm
//-lm flag to link math lib

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
}   t_data;

void ft_pixel_put(t_data *data, int x, int y, int color)
{
    char *pixel;

    pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)pixel = color;
}

void render_background(t_data *img, int color)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            ft_pixel_put(img, x, y, color);
        }
    }
}

void render_circle(t_data *img, int xc, int yc, int radius, int color)
{
    for (int x = 0; x <= radius; x++)
    {
        int y = (int)sqrt(radius * radius - x * x);
        ft_pixel_put(img, xc + x, yc + y, color);
        ft_pixel_put(img, xc + x, yc - y, color);
        ft_pixel_put(img, xc - x, yc + y, color);
        ft_pixel_put(img, xc - x, yc - y, color);
    }
}

int close_window(void *param)
{
    exit(0); // Exit the program when called
}

int key_hook(int key_code, void *param)
{
    if (key_code == XK_Escape) // XK_Escape is the keycode for the ESC key
        exit(0); // Exit the program
    return (0);
}

int main(void)
{
    t_data  img;

    img.mlx = mlx_init();
    img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Circle Example");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);

    // add background color
    render_background(&img, BLACK);

    // Draw a red circle in center w radius 100
    render_circle(&img, WIDTH / 2, HEIGHT / 2, 100, RED);

    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    
    // Register the close_window function to be called when the window is closed
    mlx_hook(img.win, 17, 0, close_window, NULL); //17 corresponds to the "DestroyNotify" event, close window when clicking "X" button 

    // Register the key_hook function to handle key events
    mlx_key_hook(img.win, key_hook, NULL);
    
    mlx_loop(img.mlx);

    return (0);
}

