/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:05:18 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 17:15:11 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_ambiant(t_minirt *minirt, char **tab)
{
	t_ambiant	*ambiant;

	if (minirt->ambiant)
	{
		printf("Error: ambiant light can't be initialized twice\n");
		exit(EXIT_FAILURE);
	}
	if (check_array_size(tab, 3) == FALSE)
		ft_error(6);
	ambiant = malloc(sizeof(t_ambiant));
	if (!ambiant)
		ft_error(7);
	ambiant->intensity = ft_assign_range(tab[1]);
	ambiant->rgb = ft_get_rgb(tab[2]);
	minirt->ambiant = ambiant;
}

void	assign_camera(t_minirt *minirt, char **tab)
{
	t_cam	*camera;

	if (minirt->camera)
	{
		printf("Error: camera light can't be initialized twice\n");
		exit(EXIT_FAILURE);
	}
	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	camera = malloc(sizeof(t_cam));
	if (!camera)
		ft_error(7);
	camera->origin = ft_get_xyz(tab[1]);
	camera->direction = ft_get_direction(tab[2]);
	camera->angle = ft_assign_angle(tab[3]);
	minirt->camera = camera;
}

void	assign_spotlight(t_minirt *minirt, char **tab)
{
	t_light	*current;
	t_light	*light;

	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	light = malloc(sizeof(t_light));
	if (!light)
		ft_error(7);
	light->origin = ft_get_xyz(tab[1]);
	light->intensity = ft_assign_range(tab[2]);
	light->rgb = ft_get_rgb(tab[3]);
	light->next = NULL;
	light->index = ++minirt->num_spotlights;
	current = minirt->lights;
	if (!current)
		minirt->lights = light;
	else
	{
		while (current->next)
		{
			current = current->next;
		}
		current->next = light;
	}
}
