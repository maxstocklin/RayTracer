/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:05:18 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/09 17:37:32 by mstockli         ###   ########.fr       */
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

t_sphere	*create_sphere(char **tab)
{
	t_sphere	*sphere;

	if (check_array_size(tab, 5) == FALSE && check_array_size(tab, 6) == FALSE)
		ft_error(6);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(7);
	return (sphere);
}

t_plane	*create_plane(char **tab)
{
	t_plane	*plane;

	if (check_array_size(tab, 5) == FALSE && check_array_size(tab, 6) == FALSE)
		ft_error(6);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		ft_error(7);
	return (plane);
}
