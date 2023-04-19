/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:02:55 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 20:51:52 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_vect	vect_cross(t_vect v1, t_vect v2)
{
	t_vect	vect_cross;

	vect_cross.x = v1.y * v2.z - v1.z * v2.y;
	vect_cross.y = v1.z * v2.x - v1.x * v2.z;
	vect_cross.z = v1.x * v2.y - v1.y * v2.x;
	return (vect_cross);
}
