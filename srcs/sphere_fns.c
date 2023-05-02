/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:29:54 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/02 12:02:45 by srapopor         ###   ########.fr       */
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
	x = x % minirt.map.width;
	y = y % minirt.map.height;
	return (int_to_rgb(mlx_get_color_value(minirt.map.texture.img, \
	*(int *)(minirt.map.texture.addr + x * (minirt.map.texture.bits_per_pixel \
	/ 8) + y * minirt.map.texture.line_length))));
}

t_vect perturb_normal(t_vect normal, t_vect tangent, double bump) {
    t_vect bitangent = vect_cross(normal, tangent); // Compute bitangent vector
    t_vect perturbed_normal = vect_add(vect_scale(normal, 1.0 - bump), vect_add(vect_scale(tangent, bump * bitangent.x), vect_scale(bitangent, bump * tangent.x)));
    return vector_normalize(perturbed_normal);
}

void	adjustnormal(double lat, double lng, t_intersect *inter, t_minirt minirt)
{
	int		x2;
	int		y2;
	t_vect	tangent;

	lat = rad_to_deg(lat + M_PI / 2);
	lng = rad_to_deg(lng + M_PI / 2) ;
	tangent = vector_normalize(vect_cross(inter->normal, make_vect(0, 1, 0)));
	x2 = (int)((lng / 180.0) * (double)minirt.bump.width / 2.0 + \
		(double)minirt.map.width / 2.0);
	y2 = (int)((lat / 90.0) * (double)minirt.bump.height / 2.0 + \
		(double)minirt.map.height / 2.0);
	x2 = x2 % minirt.bump.width;
	y2 = y2 % minirt.bump.height;
	inter->rgb = int_to_rgb(mlx_get_color_value(minirt.bump.texture.img, \
		*(int *)(minirt.bump.texture.addr + x2 * \
		(minirt.bump.texture.bits_per_pixel / 8) + \
		y2 * minirt.bump.texture.line_length)));

	inter->normal = vector_normalize(inter->normal);
	inter->normal = perturb_normal(inter->normal, tangent, inter->rgb.blue/20);
	// printf("r g b %d, %d, %d \n", inter->rgb.red, inter->rgb.green,
	// 	   inter->rgb.blue);
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

static t_intersect	ray_sphere_intersect(t_sphere *sphere, \
	t_ray ray, t_minirt minirt)
{
	t_intersect	intersect;
	// double		lat;
	// double		lng;

	(void)minirt;
	intersect.index = sphere->index;
	intersect.distance = ray_sphere_distance(sphere, ray);
	intersect.point = get_intersect(ray, intersect.distance);
	intersect.object_color = sphere->rgb;
	intersect.normal = point_subtract(intersect.point, sphere->origin);
	// lng = atan2(-intersect.normal.z, intersect.normal.x);
	// lat = acos(intersect.normal.y / vect_length(intersect.normal));
	// if (intersect.distance != -1 && minirt.show_texture)
	// 	intersect.object_color = apply_map(lat, lng, minirt);
	// if (intersect.distance != -1 && minirt.show_checkboard)
	// 	intersect.object_color = apply_checkboard(lat, lng);
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
