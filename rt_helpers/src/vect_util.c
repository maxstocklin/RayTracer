/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:55:53 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 16:03:19 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_point	make_point(double x, double y, double z)
{
	t_point	new_point;

	new_point.x = x;
	new_point.y = y;
	new_point.z = z;
	return (new_point);
}

t_vect	make_vect(double x, double y, double z)
{
	t_vect	new_vect;

	new_vect.x = x;
	new_vect.y = y;
	new_vect.z = z;
	return (new_vect);
}

t_point	get_intersect(t_ray ray, double distance)
{
	return (make_point(ray.origin.x + ray.direct.x * distance, \
		ray.origin.y + ray.direct.y * distance, ray.origin.z + \
		ray.direct.z * distance));
}

t_vect	vector_normalize(t_vect old)
{
	t_vect	new;
	double	length;

	length = vect_length(old);
	new.x = old.x / length;
	new.y = old.y / length;
	new.z = old.z / length;
	return (new);
}
