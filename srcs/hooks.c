/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:13:58 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/24 11:13:59 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ray_exit(void)
{
	exit(0);
}

int	key_hook(int keycode, t_minirt *ray)
{
	(void)ray;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	add_mlx_hook(t_minirt *ray)
{
	mlx_hook(ray->vars.win, KEYPRESS, 0, key_hook, ray);
	mlx_hook(ray->vars.win, DESTROYNOTIFY, 0, ray_exit, ray);
}
