#include "minirt.h"
#include "mlx.h"

double	ray_plane_distance(t_sphere *sphere, t_ray ray)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	distance;

	oc = point_subtract(ray.origin, sphere->origin);
	a = vect_dot(ray.direct, ray.direct);
	b = 2.0 * vect_dot(oc, ray.direct);
	c = vect_dot(oc, oc) - \
		(sphere->diameter / 2 * sphere->diameter / 2);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1);
	distance = fmin((-b + sqrt(discriminant)) / (2 * a), (-b - sqrt(discriminant)) / (2 * a));

	if (distance > 0)
		return (distance);
	else
		return (-1);
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

t_intersection	color_planes(t_minirt minirt, t_plane *plane, \
	t_ray ray, t_intersection old_intersect)
{
	t_intersection	intersect;
//	t_point	p = plane->point;
//	t_vect	n = normalizing(plane->normal);
//	vect_dot(plane->normal, ray.direct);


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
}