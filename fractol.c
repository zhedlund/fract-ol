/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:34:00 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/10 18:33:38 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int main(int argc, char **argv)
{
    t_fractal   fractal;
    
    if (argc < 2)
        help_msg;
    fractal_init(&fractal); //not done
    input_check(&fractal, argc, argv); // not done
    mlx_init(&fractal); // not done
    render_fractal(&fractal); // not done
    print_controls(); // separate from help_msg
    // mlx stuff
    return (0);
}