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
	t_rgb		base;
	t_rgb		u_plus_1;
	t_rgb		v_plus_1;
	t_vect		perturbation;
	t_adjust	a;

	lat = rad_to_deg(lat + M_PI / 2);
	lng = rad_to_deg(lng + M_PI / 2);
	a.x = (int)((lng / 180.0) * (double)minirt.bump.width / 2.0 + \
		(double)minirt.bump.width / 2.0);
	a.y = (int)((lat / 90.0) * (double)minirt.bump.height / 2.0 + \
		(double)minirt.bump.height / 2.0);
	base = get_map_rgb(a.x, a.y, minirt.bump);
	u_plus_1 = get_map_rgb(a.x + 1, a.y, minirt.bump);
	v_plus_1 = get_map_rgb(a.x, a.y + 1, minirt.bump);
	a.dx = u_plus_1.blue - base.blue;
	a.dy = v_plus_1.blue - base.blue;
	perturbation = vector_normalize(make_vect(a.dx, a.dy, 0.02 * base.blue));
	inter->normal = vector_normalize(vect_add(\
		vector_normalize(inter->normal), perturbation));
	inter->normal = vector_normalize(make_vect(base.red * 2, \
		base.green, base.blue));
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

static t_intersect	ray_sphere_intersect(t_sphere *sphere, \
	t_ray ray, t_minirt minirt)
{
	t_intersect	inter;
	double		lat;
	double		lng;

	inter.index = sphere->index;
	inter.is_sphere = true;
	inter.reflect = sphere->reflect;
	inter.distance = ray_sphere_distance(sphere, ray);
	inter.point = get_intersect(ray, inter.distance);
	inter.object_color = sphere->rgb;
	inter.normal = point_subtract(inter.point, sphere->origin);
	if (inter.distance != -1)
		inter.exit = refract_ray(ray.direct, &inter, sphere);
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
