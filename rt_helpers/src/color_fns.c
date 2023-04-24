/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:36:04 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/24 11:47:00 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

int	rgb_to_int(t_rgb rgb)
{
	return (0 << 24 | rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

t_rgb	sum_light(t_rgb color1, t_rgb color2)
{
	t_rgb	sum;

	sum.red = color1.red + color2.red;
	sum.green = color1.green + color2.green;
	sum.blue = color1.blue + color2.blue;
	if (sum.red >= 255)
		sum.red = 255;
	if (sum.green >= 255)
		sum.green = 255;
	if (sum.blue >= 255)
		sum.blue = 255;
	return (sum);
}

t_rgb	add_light(t_rgb color1, t_rgb color2, double intensity)
{
	t_rgb	res;

	res.red = (color1.red * color2.red * intensity / 255);
	res.green = (color1.green * color2.green * intensity / 255);
	res.blue = (color1.blue * color2.blue * intensity / 255);
	return (res);
}

t_rgb	add_intensity(t_rgb	rgb, double intensity)
{
	double	red;
	double	green;
	double	blue;

	red = (double)rgb.red * intensity;
	green = (double)rgb.green * intensity;
	blue = (double)rgb.blue * intensity;
	rgb.red = (int)red;
	rgb.green = (int)green;
	rgb.blue = (int)blue;
	return (rgb);
}
