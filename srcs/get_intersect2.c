/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:44:04 by max               #+#    #+#             */
/*   Updated: 2023/05/03 17:11:34 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(t_minirt minirt, t_ray ray)
{
	t_intersect		intersect;

	intersect.distance = -1;
	intersect.color = 0;
	intersect.reflect = 0;
	intersect = intersect_spheres(minirt, ray, intersect);
	intersect = intersect_cylinders(minirt, ray, intersect);
	intersect = intersect_planes(minirt, ray, intersect);
	intersect = intersect_cones(minirt, ray, intersect);
	intersect = intersect_discs(minirt, ray, intersect);
	return (intersect.color);
}
