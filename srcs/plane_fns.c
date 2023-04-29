/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:21:35 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 11:33:03 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

// Ray is parallel to plane /fabs(denom) < 0.0001
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


t_rgb 	get_checkboard_plane(t_intersect inter, t_plane *plane, t_ray ray)
{
	t_vect	p = point_subtract(inter.point, plane->point);

	p = normalize(p);
	double	d = vect_dot(p, plane->normal) / vect_dot(plane->normal, plane->normal);
	t_vect	tmp = vect_scale(plane->normal, d);
	t_point	tmpoint = make_point(tmp.x, tmp.y, tmp.z);
	t_point	ppoint = make_point(p.x, p.y, p.z);
	t_vect	p_ortho = point_subtract(ppoint, tmpoint);
	p_ortho = normalize(p_ortho);
	t_vect	v1 = ray.direct;
	t_vect	v2 = vect_cross(plane->normal, v1);
	v1 = normalize(v1);
	v2 = normalize(v2);
	
	double v1len = sqrt(vect_dot(v1, v1));
	double v2len = sqrt(vect_dot(v2, v2));

	double	u = vect_dot(p_ortho, v1) / v1len;
	double	v = vect_dot(p_ortho, v2) / v2len;


	int u_scale = 5;  // Scale factor for U coordinates
	int v_scale = 5;  // Scale factor for V coordinates
	int u_square = (int)(u * u_scale);
	int v_square = (int)(v * v_scale);
	if ((u_square + v_square) % 2 == 0) {
		// Point is in a white square
		inter.object_color.red = 255;
		inter.object_color.green = 255;
		inter.object_color.blue = 255;
	}
	else
	{
		// Point is in a black square
		inter.object_color.red = 0;
		inter.object_color.green = 0;
		inter.object_color.blue = 0;
	}
	return (inter.object_color);
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
		// lng = atan2(intersection.normal.z, intersection.normal.x);
		// lat = acos(intersection.normal.y / vect_length(intersection.normal));
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

void	closest_plane(t_ray lray, t_plane *planes, double *closest, int *index)
{
	double	test;

	while (planes)
	{
		test = ray_plane_distance(planes, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			planes = planes->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = planes->index;
			*closest = test;
		}
		planes = planes->next;
	}
}
