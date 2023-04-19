/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:00:12 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 13:02:39 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_vect	vect_scale(t_vect vect, double scale)
{
	t_vect	v_scale;

	v_scale.x = vect.x * scale;
	v_scale.y = vect.y * scale;
	v_scale.z = vect.z * scale;
	return (v_scale);
}
