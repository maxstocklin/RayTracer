/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:15:19 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/24 16:51:52 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	tests(void)
{
	double	distance;
	t_plane	*plane;
	t_ray	ray;
	t_cam	cam;

	plane = malloc(sizeof(t_plane));
	plane->point = make_point(0, 0, -99);
	plane->normal = make_vect(0, 0, 1);
	ray.origin = make_point(0, 0, 0);
	ray.direct = make_vect(0, 0, -1);
	cam.origin = make_point(-50, 0, 0);
	cam.direction = point_subtract(cam.origin, plane->point);
	distance = ray_plane_distance(plane, ray);
	printf("distance btwn r & plane %f\n", distance);
	printf("cam direction dot normal %f\n", \
		vect_dot(cam.direction, plane->normal));
}
