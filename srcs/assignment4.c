/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:05:18 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/02 00:12:23 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*create_cylinder(char **tab)
{
	t_cylinder	*cylinder;

	if (check_array_size(tab, 7) == FALSE)
		ft_error(6);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		ft_error(7);
	return (cylinder);
}

t_point	get_intersect_disc(t_vect direct, t_point origin, double distance)
{
	direct = vector_normalize(direct);
	return (make_point(origin.x + direct.x * distance, \
		origin.y + direct.y * distance, origin.z + \
		direct.z * distance));
}

t_disc	*get_disc(t_minirt *minirt, t_cylinder cylinder, t_vect normal)
{
	t_disc	*disc;

	disc = malloc(sizeof(t_disc));
	if (!disc)
		ft_error(7);
	disc->origin = get_intersect_disc(normal, \
		cylinder.origin, cylinder.height / 2);
	disc->normal = normal;
	disc->diameter = cylinder.diameter;
	disc->rgb = cylinder.rgb;
	disc->reflect = cylinder.reflect;
	disc->index = ++minirt->num_objects;
	return (disc);
}

void	assign_discs(t_minirt *minirt, t_cylinder cylinder)
{
	t_disc	*disc1;
	t_disc	*disc2;
	t_disc	*current;

	disc1 = get_disc(minirt, cylinder, cylinder.axis);
	disc2 = get_disc(minirt, cylinder, vect_scale(cylinder.axis, -1));
	disc1->next = disc2;
	disc2->next = NULL;
	current = minirt->discs;
	if (!current)
		minirt->discs = disc1;
	else
	{
		while (current->next)
			current = current->next;
		current->next = disc1;
	}
}
