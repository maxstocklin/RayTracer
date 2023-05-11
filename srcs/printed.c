/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:24:26 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/07 21:18:29 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_ambiant(t_minirt minirt)
{
	if (minirt.ambiant)
	{
		printf("AMBIANT:\n");
		printf("intensity: %f\n", minirt.ambiant->intensity);
		printf("R = %d G = %d B = %d\n", minirt.ambiant->rgb.red, \
			minirt.ambiant->rgb.green, minirt.ambiant->rgb.blue);
	}
}

void	print_camera(t_minirt minirt)
{
	if (minirt.camera)
	{
		printf("\nCAMERA:\n");
		printf("coordinates x = %f y = %f z %f\n", minirt.camera->origin.x, \
			minirt.camera->origin.y, minirt.camera->origin.z);
		printf("orientation x = %f y = %f z %f\n", minirt.camera->direction.x, \
			minirt.camera->direction.y, minirt.camera->direction.z);
		printf("Angle: %f\n", minirt.camera->angle);
	}
}

void	print_lights(t_minirt minirt)
{
	while (minirt.lights)
	{
		printf("\nSPOTLIGHT:\n");
		printf("coordinates x = %f y = %f z %f\n", minirt.lights->origin.x, \
			minirt.lights->origin.y, minirt.lights->origin.z);
		printf("intensity: %f\n", minirt.lights->intensity);
		printf("R = %d G = %d B = %d\n", minirt.lights->rgb.red, \
			minirt.lights->rgb.green, minirt.lights->rgb.blue);
		minirt.lights = minirt.lights->next;
	}
}

void	print_spheres(t_minirt minirt)
{
	while (minirt.spheres)
	{
		printf("\nSPHERE:\n");
		printf("coordinates x = %f y = %f z %f\n", minirt.spheres->origin.x, \
			minirt.spheres->origin.y, minirt.spheres->origin.z);
		printf("index = %d\n", minirt.spheres->index);
		printf("material = %d\n", minirt.spheres->material);
		printf("diameter: %f\n", minirt.spheres->diameter);
		printf("R = %d G = %d B = %d\n", minirt.spheres->rgb.red, \
			minirt.spheres->rgb.green, minirt.spheres->rgb.blue);
		minirt.spheres = minirt.spheres->next;
	}
}

void	print_planes(t_minirt minirt)
{
	while (minirt.planes)
	{
		printf("\nPLANE:\n");
		printf("coordinates x = %f y = %f z %f\n", minirt.planes->point.x, \
			minirt.planes->point.y, minirt.planes->point.z);
		printf("normal x = %f y = %f z %f\n", minirt.planes->normal.x, \
			minirt.planes->normal.y, minirt.planes->normal.z);
		printf("R = %d G = %d B = %d\n", minirt.planes->rgb.red, \
			minirt.planes->rgb.green, minirt.planes->rgb.blue);
		minirt.planes = minirt.planes->next;
	}
}
