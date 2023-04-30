/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:05:18 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 19:02:46 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_sphere(t_minirt *minirt, char **tab)
{
	t_sphere	*sphere;
	t_sphere	*current;

	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(7);
	sphere->origin = ft_get_xyz(tab[1]);
	sphere->diameter = ft_assign_diameter(tab[2]);
	sphere->rgb = ft_get_rgb(tab[3]);
	sphere->next = NULL;
	sphere->index = ++minirt->num_objects;
	current = minirt->spheres;
	if (!current)
		minirt->spheres = sphere;
	else
	{
		while (current->next)
			current = current->next;
		current->next = sphere;
	}
}

void	assign_sphere_tr(t_minirt *minirt, char **tab)
{
	t_spheretr	*spheretr;
	t_spheretr	*current;

	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	spheretr = malloc(sizeof(t_spheretr));
	if (!spheretr)
		ft_error(7);
	spheretr->origin = ft_get_xyz(tab[1]);
	spheretr->diameter = ft_assign_diameter(tab[2]);
	spheretr->rgb = ft_get_rgb(tab[3]);
	spheretr->next = NULL;
	spheretr->index = ++minirt->num_objects;
	current = minirt->spheretr;
	if (!current)
		minirt->spheretr = spheretr;
	else
	{
		while (current->next)
			current = current->next;
		current->next = spheretr;
	}
}

void	assign_plane(t_minirt *minirt, char **tab)
{
	t_plane	*plane;
	t_plane	*current;

	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		ft_error(7);
	plane->point = ft_get_xyz(tab[1]);
	plane->normal = ft_get_direction(tab[2]);
	plane->rgb = ft_get_rgb(tab[3]);
	plane->next = NULL;
	plane->index = ++minirt->num_objects;
	current = minirt->planes;
	if (!current)
		minirt->planes = plane;
	else
	{
		while (current->next)
			current = current->next;
		current->next = plane;
	}
}

void	assign_cylinder(t_minirt *minirt, char **tab)
{
	t_cylinder	*cylinder;
	t_cylinder	*current;

	if (check_array_size(tab, 6) == FALSE)
		ft_error(6);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		ft_error(7);
	cylinder->origin = ft_get_xyz(tab[1]);
	cylinder->axis = ft_get_direction(tab[2]);
	cylinder->diameter = ft_assign_diameter(tab[3]);
	cylinder->height = ft_assign_diameter(tab[4]);
	cylinder->rgb = ft_get_rgb(tab[5]);
	cylinder->next = NULL;
	cylinder->index = ++minirt->num_objects;
	current = minirt->cylinders;
	if (!current)
		minirt->cylinders = cylinder;
	else
	{
		while (current->next)
			current = current->next;
		current->next = cylinder;
	}
}

void	assign_cone(t_minirt *minirt, char **tab)
{
	t_cone	*cone;
	t_cone	*current;

	if (check_array_size(tab, 5) == FALSE)
		ft_error(6);
	cone = malloc(sizeof(t_cone));
	if (!cone)
		ft_error(7);
	cone->origin = ft_get_xyz(tab[1]);
	cone->axis = ft_get_direction(tab[2]);
	cone->angle = ft_assign_angle(tab[3]);
	cone->rgb = ft_get_rgb(tab[4]);
	cone->next = NULL;
	cone->index = ++minirt->num_objects;
	current = minirt->cones;
	if (!current)
		minirt->cones = cone;
	else
	{
		while (current->next)
			current = current->next;
		current->next = cone;
	}
}

void	ft_assignment(t_minirt *minirt, char **tab)
{
	if (ft_strcmp(tab[0], "A") == TRUE)
		assign_ambiant(minirt, tab);
	else if (ft_strcmp(tab[0], "C") == TRUE)
		assign_camera(minirt, tab);
	else if (ft_strcmp(tab[0], "L") == TRUE)
		assign_spotlight(minirt, tab);
	else if (ft_strcmp(tab[0], "sp") == TRUE)
		assign_sphere(minirt, tab);
	else if (ft_strcmp(tab[0], "tr") == TRUE)
		assign_sphere_tr(minirt, tab);
	else if (ft_strcmp(tab[0], "pl") == TRUE)
		assign_plane(minirt, tab);
	else if (ft_strcmp(tab[0], "cy") == TRUE)
		assign_cylinder(minirt, tab);
	else if (ft_strcmp(tab[0], "cn") == TRUE)
		assign_cone(minirt, tab);
	else
		ft_error(4);
}
