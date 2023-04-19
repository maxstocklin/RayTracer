/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:52:40 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 21:04:55 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

int	main(void)
{
	t_vect			vect1;
	t_vect			vect2;
	t_vect			cross;
	t_point			point;
	t_screen_size	screen;

	point = make_point(5, 12, 1);
	vect1 = make_vect(2, -4, 4);
	vect2 = make_vect(4, 0, 3);
	cross = vect_cross(vect1, vect2);
	screen.width = 800;
	screen.height = 600;
	screen_to_world(point, vect1, 150.0, screen);
	printf("cross x y z  %f %f %f\n", cross.x, cross.y, cross.z);

	return (0);
}
