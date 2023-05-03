/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:15:19 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 12:03:24 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	tests(void)
{
	t_vect	normal = make_vect(0, 0, 1);
	t_vect	incident = make_vect(1, 1, -1);
	double	n1 = 1;
	double	n2 = 1.5;
	t_vect	refracted;

	refracted = refract_vector(incident, normal, n1, n2);
	printf("refracted vector %f %f %f\n", refracted.x, refracted.y, refracted.z);
}
