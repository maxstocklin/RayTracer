/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaspherestr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:37:13 by max               #+#    #+#             */
/*   Updated: 2023/04/30 13:30:23 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

double	ray_spheretr_distance(t_spheretr *spheretr, t_ray ray)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = point_subtract(ray.origin, spheretr->origin);
	a = vect_dot(ray.direct, ray.direct);
	b = 2.0 * vect_dot(oc, ray.direct);
	c = vect_dot(oc, oc) - (spheretr->diameter / 2 * spheretr->diameter / 2);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1);
	if ((-b - sqrt(discriminant)) / (2 * a) > 0)
		return ((-b - sqrt(discriminant)) / (2 * a));
	else
		return (-1);
}

static t_intersect	ray_spheretr_intersect(t_spheretr *spheretr, \
	t_ray ray, t_minirt minirt)
{
	t_intersect	intersect;

	(void)minirt;
	intersect.index = spheretr->index;
	intersect.distance = ray_spheretr_distance(spheretr, ray);
	intersect.point = get_intersect(ray, intersect.distance);
	intersect.object_color = spheretr->rgb;
	intersect.normal = point_subtract(intersect.point, spheretr->origin);
		// lng = atan2(-intersect.normal.z, intersect.normal.x);
		// lat = acos(intersect.normal.y / vect_length(intersect.normal));
	// if (intersect.distance != -1 && minirt.show_texture)
	// 	intersect.object_color = apply_map(lat, lng, minirt);
	// if (intersect.distance != -1 && minirt.show_checkboard)
	// 	intersect.object_color = apply_checkboard(lat, lng);
	return (intersect);
}





t_rgb	get_color_tr(t_minirt minirt, t_ray ray)
{
	t_intersect		intersect;

	intersect.distance = -1;
	intersect.color = 0;
	intersect = intersect_spheres(minirt, ray, intersect);
	intersect = intersect_cylinders(minirt, ray, intersect);
	intersect = intersect_planes(minirt, ray, intersect);
	intersect = intersect_cones(minirt, ray, intersect);
	return (int_to_rgb(intersect.color));
}


t_rgb	apply_reflection(t_minirt minirt, t_intersect inter)
{
	t_vect	vdir;
	t_vect	reflection;
	t_rgb	reflect_color;
	t_ray	rayflection;

	rayflection.origin = inter.point;
	vdir = vector_normalize(point_subtract(inter.point, minirt.camera->origin));
	reflection.x = 2 * (vect_dot(inter.normal, vdir)) * inter.normal.x - vdir.x;
	reflection.y = 2 * (vect_dot(inter.normal, vdir)) * inter.normal.y - vdir.y;
	reflection.z = 2 * (vect_dot(inter.normal, vdir)) * inter.normal.z - vdir.z;
	reflection.x = -reflection.x;
	reflection.y = -reflection.y;
	reflection.z = -reflection.z;
	reflection = vector_normalize(reflection);
	rayflection.direct = reflection;
	reflect_color = get_color_tr(minirt, rayflection);
	return (reflect_color);
}

int	apply_light_tr(t_minirt minirt, t_intersect inter)
{
	inter.specular = add_intensity(inter.object_color, 0);
	inter.diffuse = add_intensity(inter.object_color, 0);
	inter.reflection = apply_reflection(minirt, inter);
	while (minirt.lights)
	{
		inter.diffuse = get_diffuse(minirt, inter, 0);
		inter.specular = get_specular(minirt, inter, 0, 0);
		minirt.lights = minirt.lights->next;
	}
	inter.rgb = sum_light(inter.ambiant, inter.specular);
	t_rgb half;
	half.red = inter.rgb.red + inter.reflection.red / 2;
	half.green = inter.rgb.green + inter.reflection.green / 2;
	half.blue = inter.rgb.blue + inter.reflection.blue / 2;
	half = sum_light(half, inter.specular);
	return (rgb_to_int(half));
}

t_intersect	apply_intersect_tr(t_intersect new, t_intersect old, t_minirt minirt)
{
	if (new.distance == -1 || (new.distance > \
		old.distance && old.distance > -1))
		return (old);
	new.ambiant = add_light(new.object_color, minirt.ambiant->rgb, \
		minirt.ambiant->intensity);
	new.color = apply_light_tr(minirt, new);
	return (new);
}

t_intersect	color_spheretr(t_minirt minirt, t_spheretr *spheretr, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	intersect = ray_spheretr_intersect(spheretr, ray, minirt);
	intersect = apply_intersect_tr(intersect, old_intersect, minirt);
	return (intersect);
}










t_intersect	intersect_spherestr(t_minirt minirt, t_ray ray, t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.spheretr)
	{
		intersect = color_spheretr(minirt, tmp.spheretr, ray, intersect);
		tmp.spheretr = tmp.spheretr->next;
	}
	return (intersect);
}



t_intersect	intersect_spheretrstr(t_minirt minirt, t_ray ray, t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.spheretr)
	{
		intersect = color_spheretr(minirt, tmp.spheretr, ray, intersect);
		tmp.spheretr = tmp.spheretr->next;
	}
	return (intersect);
}
