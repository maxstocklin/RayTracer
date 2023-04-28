/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:19:38 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/27 17:20:35 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


double	ray_cone_distance(t_cone cone, t_ray ray)
{
	double	k;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	t_vect	x;

	k = tan(deg_to_rad(cone.angle / 2));
	x = point_subtract(ray.origin, cone.origin);
	a = vect_dot(ray.direct, ray.direct) - (1 + k * k) * \
		pow(vect_dot(ray.direct, cone.axis), 2);
	b = 2 * (vect_dot(ray.direct, x) - (1 + k * k) * \
		vect_dot(ray.direct, cone.axis) * vect_dot(x, cone.axis));
	c = vect_dot(x, x) - (1 + k * k) * pow(vect_dot(x, cone.axis), 2);
	discriminant = b * b - 4 * a * c;
	// printf("disc %f\n", discriminant);
	if (discriminant < 0)
		return (-1);

	t1 = (-b - sqrt(discriminant)) / (2 * a);
//	t2 = (-b + sqrt(discriminant)) / (2 * a);
//	t = fmin(t1, t2);
	// printf("distance %f  %f\n", t1, t2);
	if (t1 < 0)
		return (-1);

	if (acos(vect_dot(vector_normalize(point_subtract(get_intersect(ray, t1),cone.origin)),cone.axis)) > M_PI/2)
		return (-1);
	return (t1);
}

t_vect	get_cone_norm(t_intersect intersection, t_cone *cone)
{
	t_vect	D;
	t_vect	normal;
	t_vect	AP;
	t_vect	proj;

	cone->axis = normalize(cone->axis);
	AP = point_subtract(intersection.point, cone->origin);
	D = cone->axis;
	proj.x = vect_dot(AP, D) / vect_dot(D, D) * D.x;
	proj.y = vect_dot(AP, D) / vect_dot(D, D) * D.y;
	proj.z = vect_dot(AP, D) / vect_dot(D, D) * D.z;
	normal = point_subtract(make_point(AP.x, AP.y, AP.z), make_point(proj.x, proj.y, proj.z));
	normal = normalize(normal);
	return (normal);
}

static t_intersect ray_cone_intersect(t_cone *cone, t_ray ray, t_minirt minirt)
{
	t_intersect	intersection;
//	t_vect		v_cam_pt;
	(void)minirt;

	intersection.index = cone->index;
	intersection.distance = ray_cone_distance(*cone, ray);
	intersection.point = get_intersect(ray, intersection.distance); // other
	intersection.object_color = cone->rgb;
	intersection.normal = get_cone_norm(intersection, cone); // other

//	v_cam_pt = vector_normalize(point_subtract(intersection.point, \
//			minirt.camera->origin));
//
//
//	if (acos(vect_dot(v_cam_pt, intersection.normal)) < M_PI / 2)
//	{
//		intersection.normal.x = -intersection.normal.x;
//		intersection.normal.y = -intersection.normal.y;
//		intersection.normal.z = -intersection.normal.z;
//	}
	return (intersection);
}

t_intersect	color_cone(t_minirt minirt, t_cone *cone, \
	t_ray ray, t_intersect old_intersect)
{
	t_intersect	intersect;

	cone->axis = normalize(cone->axis);
	intersect = ray_cone_intersect(cone, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}

void	closest_cone(t_ray lray, t_cone *cone, double *closest, int *index)
{
	double	test;

	while (cone)
	{
		test = ray_cone_distance(*cone, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			cone = cone->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = cone->index;
			*closest = test;
		}
		cone = cone->next;
	}
}
