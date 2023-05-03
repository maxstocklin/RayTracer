/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printed2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:24:26 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 17:05:35 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_cylinders(t_minirt minirt)
{
	while (minirt.cylinders)
	{
		printf("\nCYLINDER:\n");
		printf("coordinates x = %f y = %f z %f\n", minirt.cylinders->origin.x, \
			minirt.cylinders->origin.y, minirt.cylinders->origin.z);
		printf("diameter: %f\n", minirt.cylinders->diameter);
		printf("height: %f\n", minirt.cylinders->height);
		printf("R = %d G = %d B = %d\n", minirt.cylinders->rgb.red, \
			minirt.cylinders->rgb.green, minirt.cylinders->rgb.blue);
		minirt.cylinders = minirt.cylinders->next;
	}
}

void	print_cones(t_minirt minirt)
{
	while (minirt.cones)
	{
		printf("\nCONE:\n");
		printf("coordinates x = %f y = %f z %f\n", minirt.cones->origin.x, \
			minirt.cones->origin.y, minirt.cones->origin.z);
		printf("angle: %f\n", minirt.cones->angle);
		printf("R = %d G = %d B = %d\n", minirt.cones->rgb.red, \
			minirt.cones->rgb.green, minirt.cones->rgb.blue);
		minirt.cones = minirt.cones->next;
	}
}

void	print_discs(t_minirt minirt)
{
	while (minirt.discs)
	{
		printf("\nDISC:\n");
		printf("coordinates x = %f y = %f z %f\n", minirt.discs->origin.x, \
			minirt.discs->origin.y, minirt.discs->origin.z);
		printf("normal x = %f y = %f z %f\n", minirt.discs->normal.x, \
			minirt.discs->normal.y, minirt.discs->normal.z);
		printf("diameter: %f\n", minirt.discs->diameter);
		printf("R = %d G = %d B = %d\n", minirt.discs->rgb.red, \
			minirt.discs->rgb.green, minirt.discs->rgb.blue);
		minirt.discs = minirt.discs->next;
	}
}

void	ft_print_ray(t_minirt minirt)
{
	print_ambiant(minirt);
	print_camera(minirt);
	print_lights(minirt);
	print_spheres(minirt);
	print_planes(minirt);
	print_cylinders(minirt);
	print_cones(minirt);
	print_discs(minirt);
}
