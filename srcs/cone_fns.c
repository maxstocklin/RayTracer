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
	cone.angle = deg_to_rad(cone.angle);
	double cos2 = cos(cone.angle) * cos(cone.angle);
	double	sin2 = sin(cone.angle) * sin(cone.angle);
	double	t1;
	double t2;

	t_vect	p = make_vect(ray.origin.x - cone.origin.x, \
		ray.origin.y - cone.origin.y, ray.origin.z - cone.origin.z);
	t_vect	d = vector_normalize(ray.direct);
	t_vect	a = vector_normalize(cone.axis);

	double dp = d.x * p.x + d.y * p.y + d.z * p.z;
	double da = d.x * a.x + d.y * a.y + d.z * a.z;
	double ap = a.x * p.x + a.y * p.y + a.z * p.z;
	double aa = a.x * a.x + a.y * a.y + a.z * a.z;

	double A = cos2 * aa - sin2 * da * da;
	double B = 2 * cos2 * ap - 2 * sin2 * da * dp;
	double C = cos2 * (p.x * p.x + p.y * p.y + p.z * p.z) - sin2 * dp * dp;

	double discriminant = B * B - 4 * A * C;
	// printf("disc %f\n", discriminant);
	if (discriminant < 0)
		return (-1);
	t1 = (-B - sqrt(discriminant)) / (2 * A);
	t2 = (-B + sqrt(discriminant)) / (2 * A);
	double t = fmin(t1, t2);
	// printf("distance %f  %f\n", t1, t2);
	if (t < 0)
		return (-1);
	return (t);
}

t_vect	get_cone_norm(t_intersect intersection, t_cone *cone)
{
	t_vect	diff = point_subtract(intersection.point, cone->origin);
	t_vect 	proj = vect_scale(cone->axis, vect_dot(diff, cone->axis));

	t_vect normal = normalize(point_subtract(make_point(diff.x, diff.y, diff.z),make_point(proj.x, proj.y, proj.z)));
	return (normal);
}

static t_intersect ray_cone_intersect(t_cone *cone, t_ray ray, t_minirt minirt)
{
	t_intersect	intersection;
	t_vect		v_cam_pt;

	intersection.index = cone->index;
	intersection.distance = ray_cone_distance(*cone, ray);
	intersection.point = get_intersect(ray, intersection.distance); // other
	intersection.object_color = cone->rgb;
	intersection.normal = get_cone_norm(intersection, cone); // other

	v_cam_pt = vector_normalize(point_subtract(intersection.point, \
			minirt.camera->origin));
	// if (acos(vect_dot(v_cam_pt, intersection.normal)) < M_PI / 2)
	// {
	// 	intersection.normal.x = -intersection.normal.x;
	// 	intersection.normal.y = -intersection.normal.y;
	// 	intersection.normal.z = -intersection.normal.z;
	// }
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
