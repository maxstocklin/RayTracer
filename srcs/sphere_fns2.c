/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fns2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:29:54 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/08 19:42:49 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

t_rgb	apply_checkboard(double phi, double theta)
{
	double	u;
	double	v;
	int		u_square;
	int		v_square;

	u = theta / (2 * M_PI);
	v = phi / M_PI;
	u_square = (int)(u * BOARD_SCALE);
	v_square = (int)(v * BOARD_SCALE);
	if ((u_square + v_square) % 2 == 0)
		return (make_color(255, 255, 255));
	else
		return (make_color(0, 0, 0));
}

t_ray	refract_ray(t_vect incident, t_intersect *intersect, t_sphere *sphere)
{
	t_ray	iray;
	double	distance;
	t_ray	eray;

	iray.direct = refract_vector(incident, intersect->normal, 1, 1.5);
	if (iray.direct.x == 0 && iray.direct.y == 0 && \
		iray.direct.z == 0)
	{
		intersect->is_sphere = false;
		return (iray);
	}
	iray.origin = intersect->point;
	distance = ray_sphere_distance2(sphere, iray);
	if (distance == -1 || distance < 0.4)
		intersect->is_sphere = false;
	eray.origin = get_intersect(iray, distance);
	eray.direct = vector_normalize(refract_vector(incident, \
		intersect->normal, 1, 1.5));
	return (eray);
}

t_intersect	ray_sphere_intersect(t_sphere *sphere, \
	t_ray ray, t_minirt minirt)
{
	t_intersect	inter;
	double		lat;
	double		lng;

	inter.index = sphere->index;
	inter.is_sphere = 0;
	if (sphere->material == 1)
		inter.is_sphere = 1;
	inter.reflect = sphere->reflect;
	inter.distance = ray_sphere_distance(sphere, ray);
	inter.point = get_intersect(ray, inter.distance);
	inter.object_color = sphere->rgb;
	inter.normal = point_subtract(inter.point, sphere->origin);
	if (inter.distance != -1 && sphere->material == 1)
	{
		inter.exit = refract_ray(ray.direct, &inter, sphere);
	}	
	lng = atan2(-inter.normal.z, inter.normal.x);
	lat = acos(inter.normal.y / vect_length(inter.normal));
	if (inter.distance != -1 && minirt.show_texture)
	{
		adjustnormal(lat, lng, &inter, minirt);
		inter.object_color = apply_map(lat, lng, minirt);
	}
	if (inter.distance != -1 && minirt.show_checkboard && sphere->reflect < 0.1)
		inter.object_color = apply_checkboard(lat, lng);
	return (inter);
}

t_intersect	color_sphere(t_minirt minirt, t_sphere *sphere, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	intersect = ray_sphere_intersect(sphere, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
