/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:04:22 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 20:53:59 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_point	point_offset_1(t_point point, t_vect vect)
{
	t_vect	direct_norm;
	t_point	offset_point;

	direct_norm = vect_scale(vect, (1 / vect_length(vect)));
	offset_point.x = point.x + vect.x;
	offset_point.y = point.y + vect.y;
	offset_point.z = point.z + vect.z;
	return (offset_point);
}

t_point	screen_to_world(t_point origin, t_vect direct, \
	double angle, t_screen_size scr)
{
	double	world_width;
	double	world_height;
	t_point	center;

	(void)scr;
	center = point_offset_1(origin, direct);
	world_width = 2.0 * tan(deg_to_rad(angle / 2));
	printf("angle %f, angle rad %f \n", angle / 2, deg_to_rad(angle / 2));
	printf("World width %.15f\n", world_width);
	world_height = world_width * scr.height / scr.width;
	printf("World height %f\n", world_height);
	return (center);
}
