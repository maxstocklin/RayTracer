/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:23:41 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 12:58:37 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int	closest_object(t_minirt minirt, t_ray lray)
{
	double			closest;
	int				index;

	index = -1;
	closest = -1;
	closest_plane(lray, minirt.planes, &closest, &index);
	closest_sphere(lray, minirt.spheres, &closest, &index);
	closest_cylinder(lray, minirt.cylinders, &closest, &index);
	closest_cone(lray, minirt.cones, &closest, &index);
	return (index);
}

t_vect	normalize(t_vect v)
{
	double	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vect	normalized_vec = {v.x / magnitude, v.y / magnitude, v.z / magnitude};
	return (normalized_vec);
}

double vect_magnitude(t_vect v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double angle_degrees(t_vect v1, t_vect v2)
{
	double dot = vect_dot(v1, v2);
	double mag1 = vect_magnitude(v1);
	double mag2 = vect_magnitude(v2);
	double angle = acos(dot / (mag1 * mag2)) * 180.0 / M_PI;
	return angle;
}

t_rgb	get_phong(t_minirt minirt, t_intersect inter)
{
	t_rgb	tmp_phong;
	t_vect	light_dir;
	t_vect	view_dir;
	t_vect	reflection;
	double	cos_angle;
	double	cos_clamped;
	double	specular_coef;
	double	specular_power;
	double	specular;

	light_dir = point_subtract(inter.point, minirt.lights->origin);
	light_dir = normalize(light_dir);
	inter.normal = normalize(inter.normal);
	reflection.x = 2 * (vect_dot(inter.normal, light_dir)) * inter.normal.x - light_dir.x;
	reflection.y = 2 * (vect_dot(inter.normal, light_dir)) * inter.normal.y - light_dir.y;
	reflection.z = 2 * (vect_dot(inter.normal, light_dir)) * inter.normal.z - light_dir.z;
	reflection = normalize(reflection);
	view_dir = point_subtract(inter.point, minirt.camera->origin);
	view_dir = normalize(view_dir);
	cos_angle = vect_dot(reflection, view_dir);
	cos_clamped = fmax(0.0, fmin(cos_angle, 1.0));
	specular_coef = 0.9;
	specular_power = 30;
	double	power = pow(cos_clamped, specular_power);
	double	times = minirt.lights->intensity * specular_coef;
	specular = power * times;
	tmp_phong = add_intensity(minirt.lights->rgb, specular);
	return(sum_light(tmp_phong, inter.specular));
}

int	apply_light(t_minirt minirt, t_intersect inter)
{
	t_ray	lray;
	double	angle;
	double	factor;
	double	adjustment;
	t_rgb	tmp_spotlight;

	inter.specular = add_intensity(inter.object_color, 0);
	inter.diffuse = add_intensity(inter.object_color, 0);
	while (minirt.lights)
	{
		adjustment = 0;
		lray.origin = minirt.lights->origin;
		lray.direct = point_subtract(inter.point, lray.origin);
		if (closest_object(minirt, lray) != inter.index)
		{
			minirt.lights = minirt.lights->next;
			continue ;
		}
		angle = vect_angle(inter.normal, lray.direct);
		if (angle > 90)
			factor = fabs(cos(deg_to_rad(angle)));
		else
			factor = 0.0;
		adjustment = (factor * minirt.lights->intensity);
		if (adjustment >= 1.0)
			adjustment = 1;
		tmp_spotlight = add_light(inter.object_color, minirt.lights->rgb, adjustment);
		inter.diffuse = sum_light(tmp_spotlight, inter.diffuse);
		inter.specular = get_phong(minirt, inter);
		minirt.lights = minirt.lights->next;
	}
	inter.rgb = sum_light3(inter.ambiant, inter.diffuse, inter.specular);
	return (rgb_to_int(inter.rgb));
}

t_intersect	apply_intersect(t_intersect new, t_intersect old, t_minirt minirt)
{
	if (new.distance == -1 || (new.distance > \
		old.distance && old.distance > -1))
		return (old);
	new.ambiant = add_light(new.object_color, minirt.ambiant->rgb, \
		minirt.ambiant->intensity);
	new.color = apply_light(minirt, new);
	return (new);
}

void	put_pixel(t_minirt minirt, int x, int y, int color)
{
	int		*img;

	img = (int *)minirt.vars.addr;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		img[x + WIDTH * y] = color;
}

t_point	screen_to_world(t_cam *camera, int i, int j)
{
	double		world_width;
	double		px_size;
	t_point		px_position;
	t_screen	s;

	s.vup = make_vect(0, 1, 0);
	if (vect_angle(camera->direction, make_vect(1, 0, 0)) == 0)
		s.vup = make_vect(0, 0, 1);
	s.u = vect_cross(vector_normalize(camera->direction), s.vup);
	s.v = vect_cross(s.u, vector_normalize(camera->direction));
	s.center = point_offset_1(camera->origin, \
		vector_normalize(camera->direction));
	world_width = 2.0 * tan(deg_to_rad(camera->angle / 2));
	px_size = world_width / (double)WIDTH;
	s.xIncVector = vect_scale(s.u, px_size);
	s.yIncVector = vect_scale(s.v, px_size);
	s.top_left = point_apply_2vect(s.center, vect_scale(s.u, -world_width / 2), \
		vect_scale(s.v, (world_width * HEIGHT / WIDTH) / 2));
	px_position = point_apply_2vect(s.top_left, vect_scale(s.xIncVector, i), \
		vect_scale(s.yIncVector, -j));
	return (px_position);
}

void	new_draw_window(t_minirt minirt, int i, int j)
{
	t_point			vp_pt;
	t_ray			ray;
	int				color;

	mlx_clear_window(minirt.vars.mlx, minirt.vars.win);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			vp_pt = screen_to_world(minirt.camera, i, j);
			ray.origin = make_point(minirt.camera->origin.x, \
				minirt.camera->origin.y, minirt.camera->origin.z);
			ray.direct = make_vect(vp_pt.x - minirt.camera->origin.x, vp_pt.y - \
				minirt.camera->origin.y, vp_pt.z - minirt.camera->origin.z);
			color = get_color(minirt, ray);
			put_pixel(minirt, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(minirt.vars.mlx, \
	minirt.vars.win, minirt.vars.img, 0, 0);
}
