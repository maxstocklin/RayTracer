/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_obj2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:29:19 by max               #+#    #+#             */
/*   Updated: 2023/05/03 17:21:03 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int	closest_object(t_minirt minirt, t_ray lray)
{
	double			closest;
	int				index;

	index = -1;
	closest = -1;
	closest_plane(lray, minirt.planes, &closest, &index);
	closest_sphere(lray, minirt.spheres, &closest, &index);
	closest_cylinder(lray, minirt.cylinders, &closest, &index);
	closest_cone(lray, minirt.cones, &closest, &index);
	closest_disc(lray, minirt.discs, &closest, &index);
	return (index);
}
