/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:44:04 by max               #+#    #+#             */
/*   Updated: 2023/05/03 17:11:43 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersect	intersect_spheres(t_minirt minirt, t_ray ray, t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.spheres)
	{
		intersect = color_sphere(minirt, tmp.spheres, ray, intersect);
		tmp.spheres = tmp.spheres->next;
	}
	return (intersect);
}

t_intersect	intersect_cylinders(t_minirt minirt, t_ray ray, \
	t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.cylinders)
	{
		intersect = color_cylinder(minirt, tmp.cylinders, ray, intersect);
		tmp.cylinders = tmp.cylinders->next;
	}
	return (intersect);
}

t_intersect	intersect_planes(t_minirt minirt, t_ray ray, t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.planes)
	{
		intersect = color_plane(minirt, tmp.planes, ray, intersect);
		tmp.planes = tmp.planes->next;
	}
	return (intersect);
}

t_intersect	intersect_cones(t_minirt minirt, t_ray ray, t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.cones)
	{
		intersect = color_cone(minirt, tmp.cones, ray, intersect);
		tmp.cones = tmp.cones->next;
	}
	return (intersect);
}

t_intersect	intersect_discs(t_minirt minirt, t_ray ray, t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.discs)
	{
		intersect = color_disc(minirt, tmp.discs, ray, intersect);
		tmp.discs = tmp.discs->next;
	}
	return (intersect);
}
