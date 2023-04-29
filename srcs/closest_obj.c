/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:29:19 by max               #+#    #+#             */
/*   Updated: 2023/04/29 16:51:41 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	closest_sphere(t_ray lray, t_sphere *spheres, \
	double *closest, int *index)
{
	double	test;

	while (spheres)
	{
		test = ray_sphere_distance(spheres, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			spheres = spheres->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = spheres->index;
			*closest = test;
		}
		spheres = spheres->next;
	}
}

void	closest_cylinder(t_ray lray, t_cylinder *cylinder, \
	double *closest, int *index)
{
	double	test;

	while (cylinder)
	{
		test = ray_cylinder_distance(cylinder, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			cylinder = cylinder->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = cylinder->index;
			*closest = test;
		}
		cylinder = cylinder->next;
	}
}

void	closest_cone(t_ray lray, t_cone *cone, double *closest, int *index)
{
	double	test;

	while (cone)
	{
		test = ray_cone_distance(*cone, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			cone = cone->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = cone->index;
			*closest = test;
		}
		cone = cone->next;
	}
}

void	closest_plane(t_ray lray, t_plane *planes, double *closest, int *index)
{
	double	test;

	while (planes)
	{
		test = ray_plane_distance(planes, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			planes = planes->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = planes->index;
			*closest = test;
		}
		planes = planes->next;
	}
}

int	closest_object(t_minirt minirt, t_ray lray)
{
	double			closest;
	int				index;

	index = -1;
	closest = -1;
	closest_plane(lray, minirt.planes, &closest, &index);
	closest_sphere(lray, minirt.spheres, &closest, &index);
	closest_cylinder(lray, minirt.cylinders, &closest, &index);
	closest_cone(lray, minirt.cones, &closest, &index);
	return (index);
}
