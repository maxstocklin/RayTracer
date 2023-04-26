/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:23:41 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/26 10:53:34 by srapopor         ###   ########.fr       */
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
	return (index);
}

int	apply_light(t_minirt minirt, t_intersect inter)
{
	t_ray	lray;
	double	angle;
	double	factor;
	double	adjustment;
	t_rgb	total_spotlight;

	adjustment = 0;
	while (minirt.lights)
	{
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
		adjustment += (factor * minirt.lights->intensity);
		if (adjustment >= 1.0)
		{
			adjustment = 1;
			break ;
		}
		minirt.lights = minirt.lights->next;
	}
	total_spotlight = add_intensity(inter.object_color, adjustment);
	inter.rgb = sum_light(inter.rgb, total_spotlight);
	return (rgb_to_int(inter.rgb));
}

t_intersect	apply_intersect(t_intersect new, t_intersect old, t_minirt minirt)
{
	if (new.distance == -1 || (new.distance > \
		old.distance && old.distance > -1))
		return (old);
	new.rgb = add_light(new.object_color, minirt.ambiant->rgb, \
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
	double	world_width;
	double	px_size;
	t_point	px_position;
	t_point	top_left;
	t_point	center;
	t_vect	vup;
	t_vect	u;
	t_vect	v;
	t_vect xIncVector;
	t_vect yIncVector;

	vup = make_vect(0, 1, 0);
	//vup = make_vect(1, 0, 0);
	u = vect_cross(vector_normalize(camera->direction), vup);
	v = vect_cross(u, vector_normalize(camera->direction));
	center = point_offset_1(camera->origin, vector_normalize(camera->direction));
	world_width = 2.0 * tan(deg_to_rad(camera->angle / 2));
	px_size = world_width / (double)WIDTH;
	xIncVector = vect_scale(u, px_size);
	yIncVector = vect_scale(v, px_size);
	top_left = point_apply_2vect(center, vect_scale(u, -world_width / 2), \
		vect_scale(v, (world_width * HEIGHT / WIDTH) / 2));
	px_position = point_apply_2vect(top_left, vect_scale(xIncVector, i), \
		vect_scale(yIncVector, -j));
	// printf("top left x y z %f %f %f\n", top_left.x, top_left.y, top_left.z);
	// printf("xInc %f %f %f\n", xIncVector.x, xIncVector.y, xIncVector.z);
	// printf("yInc %f %f %f\n", yIncVector.x, yIncVector.y, yIncVector.z);
	return (px_position);
}

int	get_color(t_minirt minirt, t_ray ray)
{
	t_intersect		intersect;
	t_minirt		tmp_minirt;

	tmp_minirt = minirt;
	intersect.distance = -1;
	intersect.color = 0;
	while (tmp_minirt.spheres)
	{
		intersect = color_sphere(minirt, tmp_minirt.spheres, ray, intersect);
		tmp_minirt.spheres = tmp_minirt.spheres->next;
	}
	while (tmp_minirt.cylinders)
	{
		intersect = color_cylinder(minirt, tmp_minirt.cylinders, ray, intersect);
		tmp_minirt.cylinders = tmp_minirt.cylinders->next;
	}
	while (tmp_minirt.planes)
	{
		intersect = color_plane(minirt, tmp_minirt.planes, ray, intersect);
		tmp_minirt.planes = tmp_minirt.planes->next;
	}
	return (intersect.color);
}



void	new_draw_window(t_minirt minirt)
{
	t_point			vp_pt;
	t_ray			ray;
	int				i;
	int				j;
	int				color;

	i = 0;
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

			//mlx_loop_hook(minirt.vars.mlx, loop_hook, fractol);
			color = get_color(minirt, ray);
			put_pixel(minirt, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(minirt.vars.mlx, \
	minirt.vars.win, minirt.vars.img, 0, 0);
}
