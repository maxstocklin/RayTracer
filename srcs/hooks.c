/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:13:58 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 18:23:26 by srapopor         ###   ########.fr       */
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
