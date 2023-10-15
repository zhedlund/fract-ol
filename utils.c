/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:05:54 by zhedlund          #+#    #+#             */
/*   Updated: 2023/10/15 19:58:15 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(s);
		return ((char *)s + i++);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}



/*double ft_atof(const char *str) 
{
    int i;
    int sign;
    double result;
    double power;
	
	sign = 1;
	i = 0;
	result = 0.0;
	power = 1.0;
    while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
        i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
    while (ft_isdigit(str[i]))
        result = result * 10.0 + (str[i++] - '0');
    if (str[i] == '.')
        i++;
    while (ft_isdigit(str[i]))
	{
    	result = result * 10.0 + (str[i++] - '0');
        power *= 10.0;
    }
    return ((result / power) * sign);
}*/
/*#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main() {
    const char *nptr = "-123.456";
    double result = ft_atof(nptr);
    printf("Converted double: %lf\n", result);

    return 0;
}*/