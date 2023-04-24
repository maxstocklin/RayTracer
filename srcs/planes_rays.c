#include "minirt.h"
#include "mlx.h"

t_point	point_mul(t_vect vect, double scale)
{
	t_point	t_scale;

	t_scale.x = vect.x * scale;
	t_scale.y = vect.y * scale;
	t_scale.z = vect.z * scale;
	return (t_scale);
}

t_point	point_add(t_point point1, t_point point2)
{
	t_point	t_add;

	t_add.x = point1.x + point2.x;
	t_add.y = point1.y + point2.y;
	t_add.z = point1.z + point2.z;
	return (t_add);
}

t_vect normalizing(t_vect v)
{
	double	length;
	t_vect	res;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x / length;
	res.y = v.y / length;
	res.z = v.z / length;
	return (res);
}


double	ray_plane_distance(t_plane *plane, t_ray ray)
{
	double	distance;
	double	denom;

	denom = vect_dot(ray.direct, plane->normal);
	if (fabs(denom) < 0.0001)
	{
		// Ray is parallel to plane
		return (-1);
	}
	distance = vect_dot(point_subtract(plane->point, ray.origin), plane->normal) / denom;
	return (distance);
}












int	apply_light_plane(t_minirt minirt, t_intersection intersect)
{
	t_ray	lray;
	double	angle;
	double	factor;
	double	adjustment;
	t_rgb total_spotlight;

	adjustment = 0;
	while (minirt.lights)
	{
		lray.origin = minirt.lights->origin;
		lray.direct = point_subtract(intersect.point, lray.origin);
		int closest_index = closest_object(minirt, lray);
		if (closest_index != intersect.index)
		{
			minirt.lights = minirt.lights->next;
			continue;
		}
		angle = vect_angle(intersect.normal, lray.direct);
		if (angle > 90)
			factor = fabs(cos(deg_to_rad(angle)));
		else
			factor = 0;
		adjustment += (factor * minirt.lights->intensity);
		if (adjustment >= 1)
		{
			adjustment = 1;
			break ;
		}
		minirt.lights = minirt.lights->next;
	}
	total_spotlight = add_intensity(intersect.object_color, adjustment);
	intersect.rgb = sum_light(intersect.rgb, total_spotlight);
	int color;
	color = 0 << 24 | intersect.rgb.red << 16 | intersect.rgb.green << 8 | intersect.rgb.blue;
	return (color);
}

t_intersection	color_planes(t_minirt minirt, t_plane *plane, \
	t_ray ray, t_intersection old_intersect)
{
	t_intersection	intersect;

	intersect.distance = ray_plane_distance(plane, ray);
	if (intersect.distance < 0)
	{
		// Intersection point is behind ray origin
		return (old_intersect);
	}
	if (intersect.distance > old_intersect.distance && old_intersect.distance > -1)
	{
		// Intersection point is behind an object
		return (old_intersect);
	}
	intersect.point = point_add(ray.origin, point_mul(ray.direct, intersect.distance));
	intersect.normal = plane->normal;
	intersect.index = plane->index;

	intersect.object_color.red = plane->rgb.red;
	intersect.object_color.green = plane->rgb.green;
	intersect.object_color.blue = plane->rgb.blue;
	intersect.rgb = add_light(plane->rgb, minirt.ambiant->rgb, minirt.ambiant->intensity); //
	intersect.color = apply_light_plane(minirt, intersect);

	return (intersect);
}


/*
deletos



//	t_point	p = plane->point;
//	t_vect	n = normalizing(plane->normal);
//	vect_dot(plane->normal, ray.direct);

	plane.
	printf("rgb = %d", plane->rgb.red);


	double t = vect_dot(plane->normal, point_subtract(plane->point, ray.origin)) / vect_dot(plane->normal, ray.direct);
	//intersection_point = ray.origin + t * ray.direct;
	t_point intersec_point;
	intersec_point.x = ray.origin.x + t * ray.direct.x;
	intersec_point.y = ray.origin.y + t * ray.direct.y;
	intersec_point.z = ray.origin.z + t * ray.direct.z;
	if (fabs(vect_dot(point_subtract(intersec_point, plane->point), plane->normal)) < 0.000001)
		intersect.distance = vect_length(point_subtract(intersec_point, ray.origin));
	else
		return (old_intersect);

	intersect.index = plane->index;
	if (intersect.distance > old_intersect.distance && old_intersect.distance > -1)
		return (old_intersect);
	//intersect.point = get_intersect(ray, intersect.distance); //
	//intersect.normal = point_subtract(intersect.point, plane->origin); //
	intersect.object_color.red = plane->rgb.red;
	intersect.object_color.green = plane->rgb.green;
	intersect.object_color.blue = plane->rgb.blue;
	intersect.rgb = add_light(plane->rgb, minirt.ambiant->rgb, minirt.ambiant->intensity); //
	intersect.color = 0 << 24 | intersect.rgb.red << 16 | intersect.rgb.green << 8 | intersect.rgb.blue;
	return (intersect);

*/