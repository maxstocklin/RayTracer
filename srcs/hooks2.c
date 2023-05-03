/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:13:58 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 18:23:02 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
