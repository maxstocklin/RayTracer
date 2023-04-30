/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:19:58 by max               #+#    #+#             */
/*   Updated: 2023/04/30 13:30:18 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	check_height(t_cylinder *cylinder, t_ray ray, double t)
{
	double	height;
	t_vect	i;
	t_vect	diff;

	i = vect_add(make_vect(ray.origin.x, ray.origin.y, ray.origin.z), \
	vect_scale(ray.direct, t));
	diff = point_subtract(make_point(i.x, i.y, i.z), cylinder->origin);
	height = vect_dot(diff, cylinder->axis);
	return (height);
}

double	get_dist_cylinder(t_cylinder *cylinder, t_ray ray, double t1, double t2)
{
	double	height;

	height = check_height(cylinder, ray, t1);
	if (height < -cylinder->height / 2 || height > cylinder->height / 2)
	{
		height = check_height(cylinder, ray, t2);
		if (height < -cylinder->height / 2 || height > cylinder->height / 2)
			return (-1);
		else if (t2 > 0)
			return (t2);
		else
			return (-1);
	}
	if (t1 > 0)
		return (t1);
	return (-1);
}
