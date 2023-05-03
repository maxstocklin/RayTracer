/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:30:57 by max               #+#    #+#             */
/*   Updated: 2023/05/03 15:38:07 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

t_rgb	get_specular(t_minirt minirt, t_intersect inter, \
	double angle, double specular)
{
	t_rgb	tmp_phong;
	t_vect	ldir;
	t_vect	vdir;
	t_vect	reflection;

	ldir = vector_normalize(point_subtract(inter.point, minirt.lights->origin));
	inter.normal = vector_normalize(inter.normal);
	reflection.x = 2 * (vect_dot(inter.normal, ldir)) * inter.normal.x - ldir.x;
	reflection.y = 2 * (vect_dot(inter.normal, ldir)) * inter.normal.y - ldir.y;
	reflection.z = 2 * (vect_dot(inter.normal, ldir)) * inter.normal.z - ldir.z;
	reflection = vector_normalize(reflection);
	vdir = vector_normalize(point_subtract(inter.point, minirt.camera->origin));
	angle = vect_dot(reflection, vdir);
	angle = fmax(0.0, fmin(angle, 1.0));
	specular = pow(angle, PHONG_POW) * minirt.lights->intensity * PHONG_COEF;
	tmp_phong = add_intensity(minirt.lights->rgb, specular);
	return (sum_light(tmp_phong, inter.specular));
}

t_rgb	get_diffuse(t_minirt minirt, t_intersect inter, \
	double adjustment, int *check)
{
	t_rgb	tmp;
	t_ray	lray;
	double	angle;
	double	factor;

	lray.origin = minirt.lights->origin;
	lray.direct = point_subtract(inter.point, lray.origin);
	if (closest_object(minirt, lray) != inter.index)
		return (inter.diffuse);
	angle = vect_angle(inter.normal, lray.direct);
	if (angle > 90)
		factor = fabs(cos(deg_to_rad(angle)));
	else
		return (inter.diffuse);
	adjustment = (factor * minirt.lights->intensity);
	adjustment = fmin(1.0, adjustment);
	tmp = add_light(inter.object_color, minirt.lights->rgb, adjustment);
	*check = 1;
	return (sum_light(tmp, inter.diffuse));
}

t_rgb	apply_reflection(t_minirt minirt, t_intersect inter)
{
	t_vect	vdir;
	t_rgb	reflect_color;
	t_ray	rray;
	t_vect	tmp;

	vdir = vector_normalize(point_subtract(inter.point, minirt.camera->origin));
	tmp = vector_normalize(inter.normal);
	rray.direct.x = -(2 * (vect_dot(tmp, vdir)) * tmp.x - vdir.x);
	rray.direct.y = -(2 * (vect_dot(tmp, vdir)) * tmp.y - vdir.y);
	rray.direct.z = -(2 * (vect_dot(tmp, vdir)) * tmp.z - vdir.z);
	rray.direct = vector_normalize(rray.direct);
	tmp = vect_scale(rray.direct, 0.001);
	rray.origin = point_add(inter.point, make_point(tmp.x, tmp.y, tmp.z));
	rray.direct = rray.direct;
	reflect_color = int_to_rgb(get_color(minirt, rray));
	return (reflect_color);
}

t_rgb	get_mirrors(t_rgb reflection, t_rgb rgb, \
	t_rgb specular, t_intersect inter)
{
	t_rgb	mixed;
	double	coef;
	double	op;

	coef = inter.reflect;
	op = 1 - coef;
	mixed.red = (rgb.red * op) + (reflection.red * coef);
	mixed.green = (rgb.green * op) + (reflection.green * coef);
	mixed.blue = (rgb.blue * op) + (reflection.blue * coef);
	mixed = sum_light(mixed, specular);
	return (mixed);
}

int	apply_light(t_minirt minirt, t_intersect inter)
{
	t_rgb	mixed;
	int		check;

	inter.specular = add_intensity(inter.object_color, 0);
	inter.diffuse = add_intensity(inter.object_color, 0);
	if (inter.is_sphere == 1)
	{
		// printf("inter entry point %f %f %f\n", inter.point.x, inter.point.y, inter.point.z);
		// printf("inter exit point %f %f %f\n", inter.exit.origin.x, inter.exit.origin.y, inter.exit.origin.z);
		// printf("inter exit direct %f %f %f\n", inter.exit.direct.x, inter.exit.direct.y, inter.exit.direct.z);
		inter.exit_color = int_to_rgb(get_color(minirt, inter.exit));

		// inter.exit_color = make_color(0, 0, 255);
	}
	if (++minirt.mirrorlvl < 0 && inter.reflect > 0.01)
		inter.reflection = apply_reflection(minirt, inter);
	while (minirt.lights)
	{
		check = 0;
		inter.diffuse = get_diffuse(minirt, inter, 0, &check);
		if (check == 1)
			inter.specular = get_specular(minirt, inter, 0, 0);
		minirt.lights = minirt.lights->next;
	}
	if (minirt.mirrorlvl >= 0 || inter.reflect <= 0.01)
	{
		inter.rgb = sum_light3(inter.ambiant, inter.diffuse, inter.specular);
		if (inter.is_sphere == 1)
			inter.rgb = sum_light(inter.rgb, inter.exit_color);
		return (rgb_to_int(inter.rgb));
	}
	inter.rgb = sum_light(inter.ambiant, inter.diffuse);
	if (inter.is_sphere == 1)
		inter.rgb = sum_light(inter.rgb, inter.exit_color);
	mixed = get_mirrors(inter.reflection, inter.rgb, inter.specular, inter);
	return (rgb_to_int(mixed));
}
