/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:05:18 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/09 16:52:03 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*ft_get_material_sp(char *str, t_sphere *sphere)
{
	if (ft_strcmp(str, "transparent") == TRUE)
		sphere->material = 1;
	else if (ft_strcmp(str, "checkerboard") == TRUE)
		sphere->material = 2;
	else if (ft_strcmp(str, "bumpmap") == TRUE)
		sphere->material = 3;
	else
	{
		printf("material %s\n", str);
		ft_error(10);
	}	
	sphere->reflect = 0.0;
	return (sphere);
}

t_plane	*ft_get_material_pl(char *str, t_plane *plane)
{
	if (ft_strcmp(str, "checkerboard") == TRUE)
		plane->material = 2;
	else
	{
		printf("material %s\n", str);
		ft_error(10);
	}	
	return (plane);
}

void	assign_sphere(t_minirt *minirt, char **tab)
{
	t_sphere	*sphere;
	t_sphere	*current;

	if (check_array_size(tab, 5) == FALSE && check_array_size(tab, 6) == FALSE)
		ft_error(6);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(7);
	sphere->origin = ft_get_xyz(tab[1]);
	sphere->diameter = ft_assign_diameter(tab[2]);
	sphere->rgb = ft_get_rgb(tab[3]);
	sphere->reflect = ft_assign_range(tab[4]);
	sphere->material = 0;
	if (check_array_size(tab, 6) == TRUE)
		sphere = ft_get_material_sp(tab[5], sphere);
	sphere->next = NULL;
	sphere->index = ++minirt->num_objects;
	sphere->photons = NULL;
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

void	assign_plane(t_minirt *minirt, char **tab)
{
	t_plane	*plane;
	t_plane	*current;

	if (check_array_size(tab, 5) == FALSE && check_array_size(tab, 6) == FALSE)
		ft_error(6);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		ft_error(7);
	plane->point = ft_get_xyz(tab[1]);
	plane->normal = ft_get_direction(tab[2]);
	plane->rgb = ft_get_rgb(tab[3]);
	plane->reflect = ft_assign_range(tab[4]);
	plane->material = 0;
	if (check_array_size(tab, 6) == TRUE)
		plane = ft_get_material_pl(tab[5], plane);
	plane->next = NULL;
	plane->index = ++minirt->num_objects;
	plane->photons = NULL;
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

	cylinder = create_cylinder(tab);
	cylinder->origin = ft_get_xyz(tab[1]);
	cylinder->axis = ft_get_direction(tab[2]);
	cylinder->diameter = ft_assign_diameter(tab[3]);
	cylinder->height = ft_assign_diameter(tab[4]);
	cylinder->rgb = ft_get_rgb(tab[5]);
	cylinder->reflect = ft_assign_range(tab[6]);
	assign_discs(minirt, *cylinder);
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

	if (check_array_size(tab, 6) == FALSE)
		ft_error(6);
	cone = malloc(sizeof(t_cone));
	if (!cone)
		ft_error(7);
	cone->origin = ft_get_xyz(tab[1]);
	cone->axis = ft_get_direction(tab[2]);
	cone->angle = ft_assign_angle(tab[3]);
	cone->rgb = ft_get_rgb(tab[4]);
	cone->reflect = ft_assign_range(tab[5]);
	cone->next = NULL;
	cone->photons = NULL;
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
	else if (ft_strcmp(tab[0], "LS") == TRUE)
		assign_caus_light(minirt, tab);
	else if (ft_strcmp(tab[0], "sp") == TRUE)
		assign_sphere(minirt, tab);
	else if (ft_strcmp(tab[0], "pl") == TRUE)
		assign_plane(minirt, tab);
	else if (ft_strcmp(tab[0], "cy") == TRUE)
		assign_cylinder(minirt, tab);
	else if (ft_strcmp(tab[0], "cn") == TRUE)
		assign_cone(minirt, tab);
	else
		ft_error(6);
}
