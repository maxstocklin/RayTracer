/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:03:14 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 12:08:26 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

double	vect_length(t_vect vect)
{
	double	length;

	length = sqrt(pow(vect.x, 2.0) + pow(vect.y, 2.0) + pow(vect.z, 2.0));
	return (length);
}
