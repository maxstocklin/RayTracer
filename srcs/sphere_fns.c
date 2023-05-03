/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:29:54 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 15:25:53 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

double	ray_sphere_distance(t_sphere *sphere, t_ray ray)
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

double	ray_sphere_distance2(t_sphere *sphere, t_ray ray)
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
	if ((-b + sqrt(discriminant)) / (2 * a) > 0)
		return ((-b + sqrt(discriminant)) / (2 * a));
	else
		return (-1);
}

t_rgb	get_map_rgb(int x, int y, t_map map)
{
	x = x % map.width;
	y = y % map.height;
	return (int_to_rgb(mlx_get_color_value(map.texture.img, \
		*(int *)(map.texture.addr + x * (map.texture.bits_per_pixel / 8) + \
		y * map.texture.line_length))));
}

t_rgb	apply_map(double lat, double lng, t_minirt minirt)
{
	int	x;
	int	y;

	lat = rad_to_deg(lat + M_PI / 2);
	lng = rad_to_deg(lng + M_PI / 2);
	x = (int)((lng / 180.0) * (double)minirt.map.width / 2.0 + \
		(double)minirt.map.width / 2.0);
	y = (int)((lat / 90.0) * (double)minirt.map.height / 2.0 + \
		(double)minirt.map.height / 2.0);
	return (get_map_rgb(x, y, minirt.map));
}

void	adjustnormal(double lat, double lng, t_intersect *inter, \
	t_minirt minirt)
{
	int		x;
	int		y;
	t_rgb	base;
	t_rgb	u_plus_1;
	t_rgb	v_plus_1;
	int		dx;
	int		dy;
	t_vect	perturbation;

	lat = rad_to_deg(lat + M_PI / 2);
	lng = rad_to_deg(lng + M_PI / 2) ;
	x = (int)((lng / 180.0) * (double)minirt.bump.width / 2.0 + \
		(double)minirt.bump.width / 2.0);
	y = (int)((lat / 90.0) * (double)minirt.bump.height / 2.0 + \
		(double)minirt.bump.height / 2.0);
	base = get_map_rgb(x, y, minirt.bump);
	u_plus_1 = get_map_rgb(x + 1, y, minirt.bump);
	v_plus_1 = get_map_rgb(x, y + 1, minirt.bump);
	dx = u_plus_1.blue - base.blue;
	dy = v_plus_1.blue - base.blue;
	perturbation = vector_normalize(make_vect(dx, dy, 0.02 * base.blue));
	inter->normal = vector_normalize(vect_add(vector_normalize(inter->normal), perturbation));
	inter->normal = vector_normalize(make_vect(base.red*2, base.green, base.blue));
}

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
	t_ray	internal_ray;
	double	distance;
	t_ray	external_ray;

	internal_ray.direct = refract_vector(incident, intersect->normal, 1, 1.5);
	if (internal_ray.direct.x == 0 && internal_ray.direct.y == 0 && \
		internal_ray.direct.z == 0)
	{
		intersect->is_sphere = false;
		return (internal_ray);
	}
	internal_ray.origin = intersect->point;
	distance = ray_sphere_distance2(sphere, internal_ray);
	// if (distance != -1)
	// {
	// 	printf(" ray origin %f %f %f\n", internal_ray.origin.x, internal_ray.origin.y, internal_ray.origin.z);
	// 	printf("distance %f\n", distance);
	// }
	if (distance == -1 || distance < 0.4)
		intersect->is_sphere = false;
	external_ray.origin = get_intersect(internal_ray, distance);
	external_ray.direct = vector_normalize(refract_vector(incident, intersect->normal, 1, 1.5));
	return (external_ray);
}

static t_intersect	ray_sphere_intersect(t_sphere *sphere, \
	t_ray ray, t_minirt minirt)
{
	t_intersect	intersect;
	double		lat;
	double		lng;

	(void)minirt;
	intersect.index = sphere->index;
	intersect.is_sphere = true;
	intersect.reflect = sphere->reflect;
	intersect.distance = ray_sphere_distance(sphere, ray);
	intersect.point = get_intersect(ray, intersect.distance);
	intersect.object_color = sphere->rgb;
	intersect.normal = point_subtract(intersect.point, sphere->origin);
	if (intersect.distance != -1)
	{
		intersect.exit = refract_ray(ray.direct, &intersect, sphere);
	}
	lng = atan2(-intersect.normal.z, intersect.normal.x);
	lat = acos(intersect.normal.y / vect_length(intersect.normal));
	if (intersect.distance != -1 && minirt.show_texture)
	{
		adjustnormal(lat, lng, &intersect, minirt);
		intersect.object_color = apply_map(lat, lng, minirt);
	}
	//  if (intersect.distance != -1 && minirt.show_checkboard && sphere->reflect < 0.1)
	//  	intersect.object_color = apply_checkboard(lat, lng);
	return (intersect);
}

t_intersect	color_sphere(t_minirt minirt, t_sphere *sphere, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	intersect = ray_sphere_intersect(sphere, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
