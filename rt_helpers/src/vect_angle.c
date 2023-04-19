/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:06:23 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 12:31:56 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

double	vect_angle(t_vect vect1, t_vect vect2)
{
	double	angle_rad;
	double	angle_deg;

	angle_rad = acos(vect_dot(vect1, vect2) \
		/ (vect_length(vect1) * vect_length(vect2)));
	angle_deg = rad_to_deg(angle_rad);
	return (angle_deg);
}
