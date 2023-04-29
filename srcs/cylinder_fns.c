/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_fns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:19:58 by max               #+#    #+#             */
/*   Updated: 2023/04/29 16:54:52 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ray_cylinder_distance(t_cylinder *cylinder, t_ray ray)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = point_subtract(ray.origin, cylinder->origin);
	a = vect_dot(ray.direct, ray.direct) - pow(vect_dot(ray.direct, \
		cylinder->axis), 2);
	b = 2.0 * (vect_dot(ray.direct, oc) - vect_dot(ray.direct, \
	cylinder->axis) * vect_dot(oc, cylinder->axis));
	c = vect_dot(oc, oc) - pow(vect_dot(oc, cylinder->axis), 2) \
	- pow(cylinder->diameter / 2.0, 2);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1);
	else
		return (get_dist_cylinder(cylinder, ray, (-b - sqrt(discriminant)) / \
			(2.0 * a), (-b + sqrt(discriminant)) / (2.0 * a)));
}

t_vect	get_cylinder_norm(t_intersect intersection, t_cylinder *cylinder)
{
	t_vect	diff;
	t_vect	proj;
	t_vect	normal;

	diff = point_subtract(intersection.point, cylinder->origin);
	proj = vect_scale(cylinder->axis, vect_dot(diff, cylinder->axis));
	normal = vector_normalize(point_subtract(make_point(diff.x, \
		diff.y, diff.z), make_point(proj.x, proj.y, proj.z)));
	return (normal);
}

static t_intersect	ray_cylinder_intersect(t_cylinder *cylinder, \
	t_ray ray, t_minirt minirt)
{
	t_intersect	intersection;
	t_vect		v_cam_pt;

	intersection.index = cylinder->index;
	intersection.distance = ray_cylinder_distance(cylinder, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = cylinder->rgb;
	intersection.normal = get_cylinder_norm(intersection, cylinder);
	v_cam_pt = vector_normalize(point_subtract(intersection.point, \
			minirt.camera->origin));
	if (acos(vect_dot(v_cam_pt, intersection.normal)) < M_PI / 2)
	{
		intersection.normal.x = -intersection.normal.x;
		intersection.normal.y = -intersection.normal.y;
		intersection.normal.z = -intersection.normal.z;
	}
	return (intersection);
}

t_intersect	color_cylinder(t_minirt minirt, t_cylinder *cylinder, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	cylinder->axis = vector_normalize(cylinder->axis);
	intersect = ray_cylinder_intersect(cylinder, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
