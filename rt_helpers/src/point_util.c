/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:54:59 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/09 16:56:22 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_point	point_add(t_point p1, t_point p2)
{
	t_point	new;

	new.x = p1.x + p2.x;
	new.y = p1.y + p2.y;
	new.z = p1.z + p2.z;
	return (new);
}

t_point	vect_to_point(t_vect v)
{
	t_point	new;

	new.x = v.x;
	new.y = v.y;
	new.z = v.z;
	return (new);
}

t_point	point_apply_2vect(t_point origin, t_vect u, t_vect v)
{
	t_point	new;

	new.x = origin.x + u.x + v.x;
	new.y = origin.y + u.y + v.y;
	new.z = origin.z + u.z + v.z;
	return (new);
}

double	get_dist(t_point t1, t_point t2)
{
	double	res;

	res = sqrt((t2.x - t1.x) * (t2.x - t1.x) + (t2.y -t1.y) \
		* (t2.y -t1.y) + (t2.z - t1.z) * (t2.z - t1.z));
	return (res);
}