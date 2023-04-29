/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:13:58 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 12:20:59 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ray_exit(void)
{
	exit(0);
}

int	key_hook(int keycode, t_minirt *minirt)
{
	printf("hook = %d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode >= 0 && keycode < 100)
		minirt->recalc = 0;
	if (keycode == 83)
		minirt->camera->origin.z -= 5;
	if (keycode == 84)
		minirt->camera->origin.z += 5;
	if (keycode == 86)
		minirt->camera->origin.y -= 5;
	if (keycode == 87)
		minirt->camera->origin.y += 5;
	if (keycode == 89)
		minirt->camera->origin.x -= 5;
	if (keycode == 91)
		minirt->camera->origin.x += 5;
	if (keycode == 12)
		minirt->camera->direction.z -= 0.2;
	if (keycode == 13)
		minirt->camera->direction.z += 0.2;
	if (keycode == 0)
		minirt->camera->direction.y -= 0.2;
	if (keycode == 1)
		minirt->camera->direction.y += 0.2;
	if (keycode == 6)
		minirt->camera->direction.x -= 0.2;
	if (keycode == 7)
		minirt->camera->direction.x += 0.2;
	if (keycode == 17)
		minirt->show_texture = !minirt->show_texture;
	if (keycode == 49)
		minirt->show_checkboard = !minirt->show_checkboard;
	printf("origin direction %f %f %f direction %f %f %f\n", minirt->camera->origin.x, minirt->camera->origin.y, minirt->camera->origin.z, minirt->camera->direction.x, minirt->camera->direction.y, minirt->camera->direction.z);
	return (0);
}

void	add_mlx_hook(t_minirt *ray)
{
	mlx_hook(ray->vars.win, KEYPRESS, 0, key_hook, ray);
	mlx_hook(ray->vars.win, DESTROYNOTIFY, 0, ray_exit, ray);
}
