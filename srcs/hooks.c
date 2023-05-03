/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:13:58 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 17:18:13 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ray_exit(void)
{
	exit(0);
}

void	change_texture(int keycode, t_minirt *minirt)
{
	if (keycode == 17)
	{
		minirt->show_texture = !minirt->show_texture;
		minirt->show_checkboard = 0;
	}
	if (keycode == 49)
	{
		minirt->show_checkboard = !minirt->show_checkboard;
		minirt->show_texture = 0;
	}
}

void	change_origin(int keycode, t_minirt *minirt)
{
	t_sphere	*temp;

	temp = minirt->spheres;
	if (minirt->rotate_index == 0)
		change_origin_cam(keycode, minirt);
	else
	{
		while (temp)
		{
			if (minirt->rotate_index == temp->index)
				temp = change_origin_sphere(keycode, temp);
			temp = temp->next;
		}
	}
}

void	change_direction(int keycode, t_minirt *minirt)
{
	t_plane	*temp;

	temp = minirt->planes;
	if (minirt->rotate_index == 0)
		change_direction_cam(keycode, minirt);
	else
	{
		while (temp)
		{
			if (minirt->rotate_index == temp->index)
				temp->normal = change_direction_plane(keycode, temp->normal);
			temp = temp->next;
		}
	}
}

int	key_hook(int keycode, t_minirt *minirt)
{
	printf("hook = %d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode >= 0 && keycode < 100)
		minirt->recalc = 0;
	if (keycode >= 83 && keycode <= 91)
		change_origin(keycode, minirt);
	if (keycode >= 0 && keycode <= 13)
		change_direction(keycode, minirt);
	if (keycode == 17 || keycode == 49)
		change_texture(keycode, minirt);
	printf("origin direction %f %f %f direction %f %f %f\n", \
		minirt->camera->origin.x, minirt->camera->origin.y, \
		minirt->camera->origin.z, minirt->camera->direction.x, \
		minirt->camera->direction.y, minirt->camera->direction.z);
	return (0);
}

int	get_index(t_minirt minirt, t_ray ray)
{
	t_intersect		intersect;

	intersect.distance = -1;
	intersect.color = 0;
	intersect.reflect = 0;
	intersect.index = 0;
	intersect = intersect_spheres(minirt, ray, intersect);
	intersect = intersect_cylinders(minirt, ray, intersect);
	intersect = intersect_planes(minirt, ray, intersect);
	intersect = intersect_cones(minirt, ray, intersect);
	intersect = intersect_discs(minirt, ray, intersect);
	return (intersect.index);
}

int	mouse_hook(int button, int i, int j, t_minirt *minirt)
{
	t_point	vp_pt;
	t_ray	ray;

	if (button == LEFT_CLICK)
	{
		vp_pt = screen_to_world(minirt->camera, i, j);
		ray.origin = make_point(minirt->camera->origin.x, \
				minirt->camera->origin.y, minirt->camera->origin.z);
		ray.direct = make_vect(vp_pt.x - minirt->camera->origin.x, vp_pt.y - \
				minirt->camera->origin.y, vp_pt.z - minirt->camera->origin.z);
		minirt->rotate_index = get_index(*minirt, ray);
	}
	return (0);
}

void	add_mlx_hook(t_minirt *minirt)
{
	mlx_hook(minirt->vars.win, KEYPRESS, 0, key_hook, minirt);
	mlx_hook(minirt->vars.win, DESTROYNOTIFY, 0, ray_exit, minirt);
	mlx_hook(minirt->vars.win, MOUSEPRESS, 0, mouse_hook, minirt);
}
