/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:55:53 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 20:58:32 by srapopor         ###   ########.fr       */
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
