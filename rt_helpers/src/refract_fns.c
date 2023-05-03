/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract_fns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:34:42 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 12:04:01 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_vect	refract_vector(t_vect incident, t_vect normal, double n1, double n2)
{
	double	cos_theta1;
	double	sin2_theta1;
	double	sin2_theta2;
	t_vect	temp;
	t_vect	refracted;

	cos_theta1 = -vect_dot(incident, normal);
	sin2_theta1 = 1.0f - cos_theta1 * cos_theta1;
	sin2_theta2 = n1 / n2 * n1 / n2 * sin2_theta1;
	if (sin2_theta2 > 1.0)
		return (make_vect(0, 0, 0));
	temp = vect_scale(normal, n1 / n2 * cos_theta1 - sqrt(1.0 - sin2_theta2));
	refracted = vect_scale(incident, n1 / n2);
	refracted = vect_add(temp, refracted);
	return (refracted);
}
