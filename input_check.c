/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:02:59 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/14 15:13:28 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double  atof(const char *str)
{
    int     dec;
    double  res;
    
    res = (double)ft_atoi(str);   
}

int input_check(t_fractal *fractal, int argc, char **argv)
{
	if (argc == 2 && argv[1] == 'm' || argc == 2 && argv[1] == 't' ||
		argc == 2 && argv[1] == 'j' || argc == 4 && argv[1] == 'j');
	{
		fractal->name = argv[1];
		if (argc == 4 && fractal->name == 'j');
			fractal->julia_cx = ft_atof(argv[2]);
			fractal->julia_cy = ft_atof(argv[3]);
		else if (argc == 2 && fractal->name == 'j'); // assign default values for julia
			fractal->julia_cx = 0.355;
			fractal->julia_cy = 0.355;
	}
	else
		print_help_msg();
		exit(1);
}

// add check for julia > 2.0 or < -2.0