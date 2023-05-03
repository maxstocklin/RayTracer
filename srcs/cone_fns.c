/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:19:38 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/03 14:18:44 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ray_cone_distance(t_cone cone, t_ray ray)
{
	double	discriminant;
	double	t1;
	t_vect	x;

	cone.k = tan(deg_to_rad(cone.angle / 2));
	x = point_subtract(ray.origin, cone.origin);
	cone.a = vect_dot(ray.direct, ray.direct) - (1 + cone.k * cone.k) * \
		pow(vect_dot(ray.direct, cone.axis), 2);
	cone.b = 2 * (vect_dot(ray.direct, x) - (1 + cone.k * cone.k) * \
		vect_dot(ray.direct, cone.axis) * vect_dot(x, cone.axis));
	cone.c = vect_dot(x, x) - (1 + cone.k * cone.k) * \
		pow(vect_dot(x, cone.axis), 2);
	discriminant = cone.b * cone.b - 4 * cone.a * cone.c;
	if (discriminant < 0)
		return (-1);
	t1 = (-cone.b - sqrt(discriminant)) / (2 * cone.a);
	if (t1 < 0)
		return (-1);
	if (acos(vect_dot(vector_normalize(point_subtract(get_intersect(ray, t1), \
		cone.origin)), cone.axis)) > M_PI / 2)
		return (-1);
	return (t1);
}

t_vect	get_cone_norm(t_intersect intersection, t_cone *cone)
{
	t_vect	d;
	t_vect	n;
	t_vect	ap;
	t_vect	p;

	cone->axis = vector_normalize(cone->axis);
	ap = point_subtract(intersection.point, cone->origin);
	d = cone->axis;
	p.x = vect_dot(ap, d) / vect_dot(d, d) * d.x;
	p.y = vect_dot(ap, d) / vect_dot(d, d) * d.y;
	p.z = vect_dot(ap, d) / vect_dot(d, d) * d.z;
	n = point_subtract(make_point(ap.x, ap.y, ap.z), make_point(p.x, p.y, p.z));
	n = vector_normalize(n);
	return (n);
}

static t_intersect	ray_cone_intersect(t_cone *cone, t_ray ray, t_minirt minirt)
{
	t_intersect	intersection;

	(void)minirt;
	intersection.reflect = cone->reflect;
	intersection.index = cone->index;
	intersection.is_sphere = false;
	intersection.distance = ray_cone_distance(*cone, ray);
	intersection.point = get_intersect(ray, intersection.distance);
	intersection.object_color = cone->rgb;
	intersection.normal = get_cone_norm(intersection, cone);
	return (intersection);
}

t_intersect	color_cone(t_minirt minirt, t_cone *cone, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	cone->axis = vector_normalize(cone->axis);
	intersect = ray_cone_intersect(cone, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}
