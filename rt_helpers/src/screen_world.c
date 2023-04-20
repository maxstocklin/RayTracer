/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:04:22 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/19 15:13:47 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_point	point_offset_1(t_point point, t_vect vect)
{
	t_vect	direct_norm;
	t_point	offset_point;

	direct_norm = vect_scale(vect, (1 / vect_length(vect)));
	offset_point.x = point.x + vect.x;
	offset_point.y = point.y + vect.y;
	offset_point.z = point.z + vect.z;
	return (offset_point);
}




