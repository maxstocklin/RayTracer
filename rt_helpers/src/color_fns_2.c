/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_fns_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:36:04 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 16:08:41 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_rgb	sum_light3(t_rgb color1, t_rgb color2, t_rgb color3)
{
	t_rgb	sum;

	sum.red = color1.red + color2.red + color3.red;
	sum.green = color1.green + color2.green + color3.green;
	sum.blue = color1.blue + color2.blue + color3.blue;
	if (sum.red >= 255)
		sum.red = 255;
	if (sum.green >= 255)
		sum.green = 255;
	if (sum.blue >= 255)
		sum.blue = 255;
	if (sum.red <= 0)
		sum.red = 0;
	if (sum.green <= 0)
		sum.green = 0;
	if (sum.blue <= 0)
		sum.blue = 0;
	return (sum);
}

t_rgb	make_color(int r, int g, int b)
{
	t_rgb	res;

	res.red = r;
	res.green = g;
	res.blue = b;
	return (res);
}
