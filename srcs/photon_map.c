/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:56:52 by max               #+#    #+#             */
/*   Updated: 2023/05/08 23:12:18 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_photon	*get_photon(t_minirt minirt, t_ray ray)
{
	t_intersect		intersect;
	t_photon		*photon;

	photon = malloc(sizeof(t_photon));
	if (!photon)
		ft_error(7);
	photon->next = NULL;
	intersect.distance = -1;
	intersect.color = 0;
	intersect.reflect = 0;
	intersect = intersect_spheres(minirt, ray, intersect);
	intersect = intersect_cylinders(minirt, ray, intersect);
	intersect = intersect_planes(minirt, ray, intersect);
	intersect = intersect_cones(minirt, ray, intersect);
	intersect = intersect_discs(minirt, ray, intersect);

	photon->point = intersect.point;
	photon->color.red = 255 * exp(-0.2 * (intersect.distance / 2) * (intersect.distance / 2));
	photon->color.green = 255 * exp(-0.2 * (intersect.distance / 2) * (intersect.distance / 2));
	photon->color.blue = 255 * exp(-0.2 * (intersect.distance / 2) * (intersect.distance / 2));

	photon->dist = intersect.distance;
	
	// if (intersect.distance < 10)
	// 	printf("distance = %f RED %d GREEN %d BLUE %d\n", intersect.distance, photon->color.red,photon->color.green, photon->color.blue);
	photon->index = intersect.index;
	return (photon);
}

t_intersect	intersect_spheres2(t_minirt minirt, t_ray ray, t_intersect intersect)
{
	t_minirt		tmp;

	tmp = minirt;
	while (tmp.spheres)
	{
		if (tmp.spheres->material == 1)
		{
			intersect = ray_sphere_intersect(tmp.spheres, ray, minirt);
			if (intersect.distance != -1)
			{
				if (closest_object(minirt, ray) == intersect.index)
				{
					intersect.photons = get_photon(minirt, intersect.exit);
					return (intersect);
				}
			}
		}
		tmp.spheres = tmp.spheres->next;
	}
	return (intersect);
}


void	get_clights(t_minirt *minirt, t_ray ray)
{
	t_intersect		intersect;
	t_photon		*current;

	intersect.distance = -1;
	intersect.color = 0;
	intersect.reflect = 0;
	intersect = intersect_spheres2(*minirt, ray, intersect);
	if (intersect.distance == -1 || intersect.photons->dist == -1)
	{
		return ;
	}
	// if (intersect.photons->color.red == 0)
	// {
	// 	return ;
	// }

	intersect.photons->next = NULL;
	current = minirt->photons;
	if (!current)
	{
		minirt->photons = intersect.photons;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = intersect.photons;
	}
}

t_point	screen_to_world2(t_causticlight *clight, int i, int j)
{
	double		world_width;
	double		px_size;
	t_point		px_position;
	t_screen	s;

	s.vup = make_vect(0, 1, 0);
	if (vect_angle(clight->direct, make_vect(1, 0, 0)) == 0)
		s.vup = make_vect(0, 0, 1);
	s.u = vect_cross(vector_normalize(clight->direct), s.vup);
	s.v = vect_cross(s.u, vector_normalize(clight->direct));
	s.center = point_offset_1(clight->origin, \
		vector_normalize(clight->direct));
	world_width = 2.0 * tan(deg_to_rad(clight->angle / 2));
	px_size = world_width / (double)500;
	s.x_inc_vec = vect_scale(s.u, px_size);
	s.y_inc_vec = vect_scale(s.v, px_size);
	s.top_left = point_apply_2vect(s.center, vect_scale(s.u, -world_width / 2), \
		vect_scale(s.v, (world_width * 500 / 500) / 2));
	px_position = point_apply_2vect(s.top_left, vect_scale(s.x_inc_vec, i), \
		vect_scale(s.y_inc_vec, -j));
	return (px_position);
}

void	new_draw_window2(t_minirt *minirt, int i, int j)
{
	t_point			vp_pt;
	t_ray			ray;

	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			vp_pt = screen_to_world2(minirt->clights, i, j);
			ray.origin = make_point(minirt->clights->origin.x, \
				minirt->clights->origin.y, minirt->clights->origin.z);
			ray.direct = make_vect(vp_pt.x - minirt->clights->origin.x, vp_pt.y - \
				minirt->clights->origin.y, vp_pt.z - minirt->clights->origin.z);
			get_clights(minirt, ray);
			j++;		
		}
		i++;
	}
}


void	set_photon_map(t_minirt *minirt)
{
	if (minirt->clights == NULL)
		return ;
	new_draw_window2(minirt, 0, 0);
}