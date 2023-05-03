/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discs_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:13:37 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 17:14:22 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ray_disc_distance(t_disc *disc, t_ray ray)
{
	double	distance;
	t_vect	point_diff;
	double	denom;
	t_point	ipoint;
	t_vect	d;

	denom = vect_dot(disc->normal, ray.direct);
	if (fabs(denom) < 0.0001)
		return (-1);
	point_diff = point_subtract(disc->origin, ray.origin);
	distance = vect_dot(point_diff, disc->normal) / denom;
	if (distance < 0)
		return (-1);
	ipoint = get_intersect(ray, distance);
	d = point_subtract(ipoint, disc->origin);
	if (vect_length(d) > disc->diameter / 2)
	{
		return (-1);
	}
	return (distance);
}

t_intersect	ray_disc_intersect(t_disc *disc, t_ray ray, \
	t_minirt minirt)
{
	t_intersect	intersection;

	(void)minirt;
	intersection.is_sphere = false;
	intersection.reflect = disc->reflect;
	intersection.index = disc->index;
	intersection.distance = ray_disc_distance(disc, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = disc->rgb;
	intersection.normal = vector_normalize(disc->normal);
	return (intersection);
}

t_intersect	color_disc(t_minirt minirt, t_disc *disc, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	intersect = ray_disc_intersect(disc, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
