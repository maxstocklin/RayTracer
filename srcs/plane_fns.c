/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:21:35 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/24 16:43:26 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

// Ray is parallel to plane /fabs(denom) < 0.0001
double	ray_plane_distance(t_plane *plane, t_ray ray)
{
	double	distance;
	t_vect	point_diff;
	double	denom;

	denom = vect_dot(plane->normal, ray.direct);
	if (fabs(denom) < 0.0001)
		return (-1);
	point_diff = point_subtract(plane->point, ray.origin);
	distance = vect_dot(point_diff, plane->normal) / denom;
	if (distance < 0)
		return (-1);
	return (distance);
}

static t_intersect	ray_plane_intersect(t_plane *plane, t_ray ray)
{
	t_intersect	intersection;

	intersection.index = plane->index;
	intersection.distance = ray_plane_distance(plane, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = plane->rgb;
	intersection.normal = plane->normal;
	return (intersection);
}

t_intersect	color_plane(t_minirt minirt, t_plane *plane, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	intersect = ray_plane_intersect(plane, ray);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}

void	closest_plane(t_ray lray, t_plane *planes, double *closest, int *index)
{
	double	test;

	while (planes)
	{
		test = ray_plane_distance(planes, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			planes = planes->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = planes->index;
			*closest = test;
		}
		planes = planes->next;
	}
}
