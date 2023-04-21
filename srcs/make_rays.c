/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:23:41 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/21 14:38:50 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

t_point	get_intersect(t_ray ray, double distance)
{
	return (make_point(ray.origin.x + ray.direct.x * distance, \
		ray.origin.y  + ray.direct.y * distance, ray.origin.z + \
		ray.direct.z * distance));
}

double	ray_sphere_distance(t_sphere *sphere, t_ray ray)
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

t_rgb	add_intensity(t_rgb	rgb, double intensity)
{
	double	red;
	double	green;
	double	blue;

	red = (double)rgb.red * intensity;
	green = (double)rgb.green * intensity;
	blue = (double)rgb.blue * intensity;
	rgb.red = (int)red;
	rgb.green = (int)green;
	rgb.blue = (int)blue;
	return (rgb);
}

t_rgb sum_light(t_rgb color1, t_rgb color2)
{
	t_rgb sum;

	sum.red = color1.red + color2.red;
	sum.green = color1.green + color2.green;
	sum.blue = color1.blue + color2.blue;
	if (sum.red >= 255)
		sum.red = 255;
	if (sum.green >= 255)
		sum.green = 255;
	if (sum.blue >= 255)
		sum.blue = 255;
	return (sum);
}

int	closest_object(t_minirt minirt, t_ray lray)
{
	double			closest;
	double			test;
	int 			index = -1;

	closest = -1;
	while (minirt.spheres)
	{
		test = ray_sphere_distance(minirt.spheres, lray);

		if (test == -1 || (test > closest && closest > -1))
		{
			minirt.spheres = minirt.spheres->next;
			continue;
		}
		if (closest == -1 || test < closest)
		{
			index = minirt.spheres->index;
			closest = test;
		}
		minirt.spheres = minirt.spheres->next;
	}
	return (index);
}

int	apply_light(t_minirt minirt, t_intersection intersect)
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

t_rgb	add_light(t_rgb color1, t_rgb color2, double intensity)
{
	t_rgb res;

	res.red = (color1.red * color2.red * intensity / 255);
	res.green = (color1.green * color2.green * intensity / 255);
	res.blue = (color1.blue * color2.blue * intensity / 255);
	return (res);
}

t_intersection	color_sphere(t_minirt minirt, t_sphere *sphere, \
	t_ray ray, t_intersection old_intersect)
{
	t_intersection	intersect;

	(void)minirt;
	intersect.index = sphere->index;
	intersect.distance = ray_sphere_distance(sphere, ray);
	if (intersect.distance == -1 || (intersect.distance > \
		old_intersect.distance && old_intersect.distance > -1))
		return (old_intersect);
	intersect.point = get_intersect(ray, intersect.distance);
	intersect.normal = point_subtract(intersect.point, sphere->origin);
	intersect.object_color.red = sphere->rgb.red;
	intersect.object_color.green = sphere->rgb.green;
	intersect.object_color.blue = sphere->rgb.blue;
	intersect.rgb = add_light(sphere->rgb, minirt.ambiant->rgb, minirt.ambiant->intensity);
	intersect.color = apply_light(minirt, intersect);
	return (intersect);
}

void	put_pixel(t_minirt minirt, int x, int y, int color)
{
	int		*img;

	img = (int *)minirt.vars.addr;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		img[x + WIDTH * y] = color;
}

t_point	screen_to_world(t_cam *camera, int i, int j)
{
	double	world_width;
	double	px_size;
	t_point	px_position;
	t_point	top_left;
	t_point	center;

	center = point_offset_1(camera->origin, camera->direction);
	world_width = 2.0 * tan(deg_to_rad(camera->angle / 2));
	px_size = world_width / (double)WIDTH;
	top_left = make_point(center.x - world_width / 2, center.y + \
		(world_width * HEIGHT / WIDTH) / 2, center.z);
	px_position = make_point(top_left.x + (double)i * px_size, \
		top_left.y - (double)j * px_size, top_left.z);
	return (px_position);
}

int	get_color(t_minirt minirt, t_ray ray)
{
	t_intersection	intersection;
	t_minirt		temp;

	temp = minirt;
	intersection.distance = -1;
	intersection.color = 0;
	while(temp.spheres)
	{
		intersection.index = temp.spheres->index;
		intersection = color_sphere(minirt, temp.spheres, ray, intersection);
		temp.spheres = temp.spheres->next;
	}
	while(temp.planes)
	{
		intersection.index = temp.planes->index;
		intersection = color_planes(minirt, temp.planes, ray, intersection);
		temp.planes = temp.planes->next;
	}
	return (intersection.color);
}

void	new_draw_window(t_minirt minirt)
{
	t_point			vp_pt;
	t_ray			ray;
	int				i;
	int				j;
	int				color;

	i = 0;
	mlx_clear_window(minirt.vars.mlx, minirt.vars.win);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			vp_pt = screen_to_world(minirt.camera, i, j);
			ray.origin = make_point(minirt.camera->origin.x, \
				minirt.camera->origin.y, minirt.camera->origin.z);
			ray.direct = make_vect(vp_pt.x - minirt.camera->origin.x, vp_pt.y - \
				minirt.camera->origin.y, vp_pt.z - minirt.camera->origin.z);
			color = get_color(minirt, ray);
			put_pixel(minirt, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(minirt.vars.mlx, \
	minirt.vars.win, minirt.vars.img, 0, 0);
}
