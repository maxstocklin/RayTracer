/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:59:16 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 12:07:21 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

double	vect_dot(t_vect vect1, t_vect vect2)
{
	double	dot;

	dot = (vect1.x * vect2.x) + (vect1.y * vect2.y) + (vect1.z * vect2.z);
	return (dot);
}
