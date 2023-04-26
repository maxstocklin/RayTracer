/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:29:54 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/25 14:47:53 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

//	removed for norminette
// distance = fmin((-b + sqrt(discriminant)) / (2 * a), \
// 	(-b - sqrt(discriminant)) / (2 * a));
static double	ray_sphere_distance(t_sphere *sphere, t_ray ray)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = point_subtract(ray.origin, sphere->origin);
	a = vect_dot(ray.direct, ray.direct);
	b = 2.0 * vect_dot(oc, ray.direct);
	c = vect_dot(oc, oc) - (sphere->diameter / 2 * sphere->diameter / 2);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1);
	if ((-b - sqrt(discriminant)) / (2 * a) > 0)
		return ((-b - sqrt(discriminant)) / (2 * a));
	else
		return (-1);
}

static t_intersect ray_sphere_intersect(t_sphere *sphere, t_ray ray)
{
	t_intersect	intersection;

	intersection.index = sphere->index;
	intersection.distance = ray_sphere_distance(sphere, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = sphere->rgb;
	intersection.normal = point_subtract(intersection.point, sphere->origin);
	return (intersection);
}

void closest_sphere(t_ray lray, t_sphere *spheres, double *closest, int *index)
{
	double	test;

	while (spheres)
	{
		test = ray_sphere_distance(spheres, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			spheres = spheres->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = spheres->index;
			*closest = test;
		}
		spheres = spheres->next;
	}
}

t_intersect	color_sphere(t_minirt minirt, t_sphere *sphere, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	intersect = ray_sphere_intersect(sphere, ray);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
