/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:21:35 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/30 20:29:57 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

double	ray_plane_distance(t_plane *plane, t_ray ray)
{
	double	distance;
	t_vect	point_diff;
	double	denom;

	denom = vect_dot(plane->normal, ray.direct);
	if (fabs(denom) < 0.0001)
		return (-1);
	point_diff = point_subtract(plane->point, ray.origin);
	distance = vect_dot(point_diff, plane->normal) / denom;
	if (distance < 0)
		return (-1);
	return (distance);
}

t_vect	get_arbitrary(t_plane *plane, t_ray ray)
{
	t_vect	arbitrary;

	arbitrary = make_vect(0.0, 1.0, 0.0);
	if (plane->normal.x == 0 && (plane->normal.y == 1.0 ||  plane->normal.y == -1.0) && plane->normal.z == 0)
		arbitrary = make_vect(1.0, 0.0, 0.0);
	
	(void)ray;
	// to make a dart target
	//t_vect	arbitrary = ray.direct;
	return (arbitrary);
}

t_rgb	checkboard_plane(t_intersect inter, t_plane *plane, t_ray ray)
{
	t_vect	x;
	t_vect	y;
	t_vect	arbitrary;
	t_vect	relativePos;
	double	x_coord;
	double	y_coord;

	(void)ray;
	relativePos = point_subtract(inter.point, plane->point);
	arbitrary = get_arbitrary(plane, ray);
	x = vector_normalize(vect_cross(plane->normal, arbitrary));
	y = vector_normalize(vect_cross(plane->normal, x));
	x_coord = vect_dot(relativePos, x) + BOARD_SCALE * 20.0; // weird way to solve the double whites and blacks problem
	y_coord = vect_dot(relativePos, y) + BOARD_SCALE * 20.0;
	if (((int)(x_coord / BOARD_SCALE) + (int)(y_coord / BOARD_SCALE)) % 2 == 0)
		return (make_color(255, 255, 255));
	else
		return (make_color(0, 0, 0));
}

static t_intersect	ray_plane_intersect(t_plane *plane, t_ray ray, \
	t_minirt minirt)
{
	t_intersect	intersection;
	t_vect		v_cam_pln;

	intersection.index = plane->index;
	v_cam_pln = vector_normalize(point_subtract(plane->point, \
			minirt.camera->origin));
	if (acos(vect_dot(v_cam_pln, plane->normal)) < M_PI / 2)
	{
		plane->normal.x = -plane->normal.x;
		plane->normal.y = -plane->normal.y;
		plane->normal.z = -plane->normal.z;
	}
	intersection.distance = ray_plane_distance(plane, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = plane->rgb;
	intersection.normal = vector_normalize(plane->normal);
	if (intersection.distance != -1 && minirt.show_checkboard)
	{
		intersection.object_color = checkboard_plane(intersection, plane, ray);
	}
	return (intersection);
}

t_intersect	color_plane(t_minirt minirt, t_plane *plane, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	intersect = ray_plane_intersect(plane, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
