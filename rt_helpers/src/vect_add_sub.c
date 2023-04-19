/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_add_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:45:18 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/19 16:10:21 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_vect	vect_add(t_vect vect1, t_vect vect2)
{
	t_vect	v_add;

	v_add.x = vect1.x + vect2.x;
	v_add.y = vect1.y + vect2.y;
	v_add.z = vect1.z + vect2.z;
	return (v_add);
}

t_vect	point_subtract(t_point p1, t_point p2)
{
	t_vect	v_sub;

	v_sub.x = p1.x - p2.x;
	v_sub.y = p1.y - p2.y;
	v_sub.z = p1.z - p2.z;
	return (v_sub);
}
