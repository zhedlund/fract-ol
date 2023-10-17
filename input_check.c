/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:02:59 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/17 14:57:44 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atof(const char *str)
{
    double	result;
    double	power;
    char	*dec_point;
	int		sign;
	int		i;

	sign = 1;
	power = 1.0;
	if (str[0] == '-')
	{
        sign = -1;
        str++;
    }
	result = (double)ft_atoi(str++);
	dec_point = ft_strchr(str, '.');
    if (dec_point) 
	{
        i = dec_point - str + 1;
        while (ft_isdigit(str[i]))
		{
            result = result * 10.0 + (str[i++] - '0');
            power *= 10.0;
        }
    }
    return (result * sign / power);
}

int input_check(t_fractal *fractal, int argc, char **argv)
{
	fractal->name = *argv[1];
	if (argc == 2) // assign default values for julia
	{	
		fractal->julia_cx = 0.355;
		fractal->julia_cy = 0.355;
	}
	else if (fractal->name == 'j' && argc == 4)
	{
		fractal->julia_cx = ft_atof(argv[2]);
		fractal->julia_cy = ft_atof(argv[3]);
			if (fractal->julia_cx < -2.0 || fractal->julia_cx > 2.0
			|| fractal->julia_cy < -2.0 || fractal->julia_cy > 2.0)
			{
				print_help_msg();
				exit(1);
			}
	}
	else
	{
		print_help_msg();
		exit(1);
	}
	return (0);
}