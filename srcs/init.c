/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:07:50 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/02 13:50:05 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	ft_get_rgb(char *str)
{
	char	**dest;
	t_rgb	rgb;

	if (ft_check_rgb(str) == FALSE)
	{
		ft_error(2);
	}
	dest = ft_split(str, ',');
	rgb.red = ft_atoi(dest[0]);
	rgb.green = ft_atoi(dest[1]);
	rgb.blue = ft_atoi(dest[2]);
	if (ft_check_rgb_255(rgb) == FALSE)
		ft_error(2);
	ft_free_array(dest);
	return (rgb);
}

t_point	ft_get_xyz(char *str)
{
	t_point	xyz;
	char	**dest;

	if (ft_check_xyz(str) == FALSE)
	{
		ft_error(3);
	}
	dest = ft_split(str, ',');
	xyz.x = ft_atod(dest[0], 1, 0, 1);
	xyz.y = ft_atod(dest[1], 1, 0, 1);
	xyz.z = ft_atod(dest[2], 1, 0, 1);
	if (ft_check_xyz_int(xyz) == FALSE)
		ft_error(3);
	ft_free_array(dest);
	return (xyz);
}

t_vect	ft_get_direction(char *str)
{
	t_vect	xyz;
	char	**dest;

	if (ft_check_xyz(str) == FALSE)
	{
		ft_error(5);
	}
	dest = ft_split(str, ',');
	xyz.x = ft_atod(dest[0], 1, 0, 1);
	xyz.y = ft_atod(dest[1], 1, 0, 1);
	xyz.z = ft_atod(dest[2], 1, 0, 1);
	if (ft_check_direction_int(xyz) == FALSE)
		ft_error(5);
	ft_free_array(dest);
	return (xyz);
}

void	ft_set_null(t_minirt *minirt)
{
	minirt->ambiant = NULL;
	minirt->camera = NULL;
	minirt->spheres = NULL;
	minirt->lights = NULL;
	minirt->cylinders = NULL;
	minirt->cones = NULL;
	minirt->planes = NULL;
	minirt->num_objects = 0;
	minirt->num_spotlights = 0;
	minirt->recalc = 0;
	minirt->show_texture = 0;
	minirt->show_checkboard = 0;
	minirt->mirrorlvl = 0;
	minirt->rotate_index = 0;
}
