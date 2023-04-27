#include "minirt.h"

double get_dist_cylinder(double discriminant, double b, t_cylinder *cylinder, t_ray ray, double a)
{
	double	t1;
	double	t2;
	double	height;
	t_vect	intersect_point;
	t_vect	diff;

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	intersect_point = vect_add(make_vect(ray.origin.x, ray.origin.y, ray.origin.z), \
	vect_scale(ray.direct, t1));
	diff = point_subtract(make_point(intersect_point.x, intersect_point.y, intersect_point.z), cylinder->origin);
	height = vect_dot(diff, cylinder->axis);
	if (height < -cylinder->height / 2 || height > cylinder->height / 2) {
		intersect_point = vect_add(make_vect(ray.origin.x, ray.origin.y, ray.origin.z), \
        vect_scale(ray.direct, t2));
		diff = point_subtract(make_point(intersect_point.x, intersect_point.y, intersect_point.z), cylinder->origin);
		height = vect_dot(diff, cylinder->axis);
		if (height < -cylinder->height / 2 || height > cylinder->height / 2)
			return (-1);
		else if (t2 > 0)
			return (t2);
		else
			return (-1);
	}
	if (t1 > 0)
		return (t1);
	return (-1);
}

static double	ray_cylinder_distance(t_cylinder *cylinder, t_ray ray)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = point_subtract(ray.origin, cylinder->origin);
	a = vect_dot(ray.direct, ray.direct) - pow(vect_dot(ray.direct, cylinder->axis), 2);
	b = 2.0 * (vect_dot(ray.direct, oc) - vect_dot(ray.direct, cylinder->axis) * vect_dot(oc, cylinder->axis));
	c = vect_dot(oc, oc) - pow(vect_dot(oc, cylinder->axis), 2) - pow(cylinder->diameter/2.0, 2);
	discriminant = (b * b) - (4 * a * c);

	//printf("discr = %f\n", discriminant);
	if (discriminant < 0)
		return (-1);
	else
		return (get_dist_cylinder(discriminant, b, cylinder, ray, a));
}

t_vect	get_cylinder_norm(t_intersect intersection, t_cylinder *cylinder)
{
	t_vect	diff = point_subtract(intersection.point, cylinder->origin);
	t_vect 	proj = vect_scale(cylinder->axis, vect_dot(diff, cylinder->axis));

	t_vect normal = normalize(point_subtract(make_point(diff.x, diff.y, diff.z),make_point(proj.x, proj.y, proj.z)));
	return (normal);
}

static t_intersect ray_cylinder_intersect(t_cylinder *cylinder, t_ray ray, t_minirt minirt)
{
	t_intersect	intersection;
	t_vect		v_cam_pt;

	intersection.index = cylinder->index;
	intersection.distance = ray_cylinder_distance(cylinder, ray);
	intersection.point = get_intersect(ray, intersection.distance); // other
	intersection.object_color = cylinder->rgb;
	intersection.normal = get_cylinder_norm(intersection, cylinder); // other

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

	cylinder->axis = normalize(cylinder->axis);
	intersect = ray_cylinder_intersect(cylinder, ray, minirt);
	intersect = apply_intersect(intersect, old_intersect, minirt);
	return (intersect);
}

void	closest_cylinder(t_ray lray, t_cylinder *cylinder, double *closest, int *index)
{
	double	test;

	while (cylinder)
	{
		test = ray_cylinder_distance(cylinder, lray);
		if (test == -1 || (test > *closest && *closest > -1))
		{
			cylinder = cylinder->next;
			continue ;
		}
		if (*closest == -1 || test < *closest)
		{
			*index = cylinder->index;
			*closest = test;
		}
		cylinder = cylinder->next;
	}
}




















