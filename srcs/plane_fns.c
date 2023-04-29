/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:21:35 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 17:18:14 by max              ###   ########.fr       */
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

t_rgb	get_checkboard_plane(t_intersect inter, t_plane *plane, t_ray ray)
{
	t_vect	p;
	double	d;
	t_vect	tmp;
	t_point	tmpoint;
	t_point	ppoint;
	t_vect	p_ortho;
	t_vect	v1;
	t_vect	v2;
	double	v1len;
	double	v2len;
	double	u;
	double	v;
	int		u_square;
	int		v_square;

	p = vector_normalize(point_subtract(inter.point, plane->point));
	d = vect_dot(p, plane->normal) / vect_dot(plane->normal, plane->normal);
	tmp = vect_scale(plane->normal, d);
	tmpoint = make_point(tmp.x, tmp.y, tmp.z);
	ppoint = make_point(p.x, p.y, p.z);
	p_ortho = vector_normalize(point_subtract(ppoint, tmpoint));
	v1 = ray.direct;
	v2 = vect_cross(plane->normal, v1);
	v1 = vector_normalize(v1);
	v2 = vector_normalize(v2);
	v1len = sqrt(vect_dot(v1, v1));
	v2len = sqrt(vect_dot(v2, v2));
	u = vect_dot(p_ortho, v1) / v1len;
	v = vect_dot(p_ortho, v2) / v2len;
	u_square = (int)(u * BOARD_SCALE);
	v_square = (int)(v * BOARD_SCALE);
	if ((u_square + v_square) % 2 == 0)
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
	intersection.normal = plane->normal;
	if (intersection.distance != -1 && minirt.show_checkboard)
	{
		intersection.object_color = get_checkboard_plane(intersection, plane, ray);
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
