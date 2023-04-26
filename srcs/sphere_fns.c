/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:29:54 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/27 11:33:55 by srapopor         ###   ########.fr       */
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

void	adjustcolor(double lat, double lng, t_intersect *intersect, t_minirt minirt)
{
	int	x;
	int	y;

	// printf("lng lat %f %f\n", lng, lat);
	lat = rad_to_deg(lat + M_PI/2);
	lng = rad_to_deg(lng + M_PI/2) ;
	(void)intersect;
	(void)minirt;

	x = (int)((lng / 180.0) * (double)minirt.map.width/ 2.0 + (double)minirt.map.width / 2.0);
	y = (int)((lat / 90.0) * (double)minirt.map.height / 2.0 + (double)minirt.map.height / 2.0);
	// printf("x y %d %d\n", x, y);
	x = x % minirt.map.width;
	y = y % minirt.map.height;

	intersect->object_color = int_to_rgb(mlx_get_color_value(minirt.map.texture.img, \
		*(int *)(minirt.map.texture.addr + x * (minirt.map.texture.bits_per_pixel / 8) + y * minirt.map.texture.line_length)));
	// printf("%x r g b %d, %d, %d \n", *(minirt.map.texture.addr + x + y * minirt.map.width), intersect->object_color.red, intersect->object_color.green, intersect->object_color.blue);
}

static t_intersect ray_sphere_intersect(t_sphere *sphere, t_ray ray, t_minirt minirt)
{
	t_intersect	intersection;
	double		lat;
	double		lng;

	(void)minirt;
	intersection.index = sphere->index;
	intersection.distance = ray_sphere_distance(sphere, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = sphere->rgb;
	intersection.normal = point_subtract(intersection.point, sphere->origin);
	if (intersection.distance != -1 && minirt.show_texture)
	{
		lng = atan2(intersection.normal.y, intersection.normal.x);
		lat = acos(intersection.normal.z / vect_length(intersection.normal));
		adjustcolor(lat, lng, &intersection, minirt);
	}
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

	intersect = ray_sphere_intersect(sphere, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
