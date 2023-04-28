/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:29:54 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/28 17:40:51 by srapopor         ###   ########.fr       */
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

t_rgb 	get_checkboard(double phi, double theta, t_intersect inter)
{
	double	u = theta / (2 * M_PI);
	double	v = phi / M_PI;
	int u_scale = 20;  // Scale factor for U coordinates
	int v_scale = 20;  // Scale factor for V coordinates
	int u_square = (int)(u * u_scale);
	int v_square = (int)(v * v_scale);
	if ((u_square + v_square) % 2 == 0) {
		// Point is in a white square
		inter.object_color.red = 255;
		inter.object_color.green = 255;
		inter.object_color.blue = 255;
	}
	else
	{
		// Point is in a black square
		inter.object_color.red = 0;
		inter.object_color.green = 0;
		inter.object_color.blue = 0;
	}
	return (inter.object_color);
}

static t_intersect ray_sphere_intersect(t_sphere *sphere, t_ray ray, t_minirt minirt)
{
	t_intersect	intersection;
	double		lat;
	double		lng;

	intersection.index = sphere->index;
	intersection.distance = ray_sphere_distance(sphere, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = sphere->rgb;
	intersection.normal = point_subtract(intersection.point, sphere->origin);
	if (intersection.distance != -1 && minirt.show_texture)
	{
		lng = atan2(-intersection.normal.z, intersection.normal.x);
		lat = acos(intersection.normal.y / vect_length(intersection.normal));
		adjustnormal(lat, lng, &intersection, minirt);
		adjustcolor(lat, lng, &intersection, minirt);
	}
	if (intersection.distance != -1 && minirt.show_checkboard)
	{
		lng = atan2(intersection.normal.z, intersection.normal.x);
		lat = acos(intersection.normal.y / vect_length(intersection.normal));
		intersection.object_color = get_checkboard(lat, lng, intersection);
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
