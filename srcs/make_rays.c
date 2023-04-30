/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:23:41 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 20:17:34 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

double	angle_degrees(t_vect v1, t_vect v2)
{
	double	dot;
	double	mag1;
	double	mag2;
	double	angle;

	dot = vect_dot(v1, v2);
	mag1 = vect_length(v1);
	mag2 = vect_length(v2);
	angle = acos(dot / (mag1 * mag2)) * 180.0 / M_PI;
	return (angle);
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
	s.x_inc_vec = vect_scale(s.u, px_size);
	s.y_inc_vec = vect_scale(s.v, px_size);
	s.top_left = point_apply_2vect(s.center, vect_scale(s.u, -world_width / 2), \
		vect_scale(s.v, (world_width * HEIGHT / WIDTH) / 2));
	px_position = point_apply_2vect(s.top_left, vect_scale(s.x_inc_vec, i), \
		vect_scale(s.y_inc_vec, -j));
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
