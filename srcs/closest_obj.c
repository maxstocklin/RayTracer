/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:29:19 by max               #+#    #+#             */
/*   Updated: 2023/05/03 17:21:11 by srapopor         ###   ########.fr       */
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

void	closest_disc(t_ray lray, t_disc *disc, double *closest, int *index)
{
	double	test;

	while (disc)
	{
		test = ray_disc_distance(disc, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			disc = disc->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = disc->index;
			*closest = test;
		}
		disc = disc->next;
	}
}
