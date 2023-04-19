/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:23:41 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/19 16:32:55 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int color_sphere(t_minirt minirt, t_ray ray) {
	t_vect	oc = point_subtract(ray.origin,	minirt.spheres->origin);

	double a = vect_dot(ray.direct, ray.direct);
    double b = 2.0 * vect_dot(oc, ray.direct);
    double c = vect_dot(oc, oc) - \
		(minirt.spheres->diameter/2   * minirt.spheres->diameter/2);
    double discriminant = b*b - 4*a*c;
	if (discriminant > 0 && discriminant < 20)
			return (0 << 24 | 0 << 16 | 255 << 8 | 0);

	else if (discriminant > 0)
	{	printf("discreminant = %f \n", discriminant);
		return (0 << 24 | (int)(minirt.spheres->rgb.red) << 16 | \
		(int)(minirt.spheres->rgb.green) << 8 | \
		(int)(minirt.spheres->rgb.blue));
	}
	else
		return (0 << 24 | (int)(minirt.ambiant->intensity * minirt.ambiant->rgb.red) << 16 | \
		(int)(minirt.ambiant->intensity * minirt.ambiant->rgb.green) << 8 | (\
		int)(minirt.ambiant->intensity * minirt.ambiant->rgb.blue));
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
			color = color_sphere(minirt, ray); // todo:  apply_ray(minirt, ray);
			put_pixel(minirt, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(minirt.vars.mlx, \
	minirt.vars.win, minirt.vars.img, 0, 0);
}