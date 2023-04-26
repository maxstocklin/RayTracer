/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:15:19 by srapopor          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/26 15:05:42 by srapopor         ###   ########.fr       */
=======
/*   Updated: 2023/04/24 16:51:52 by srapopor         ###   ########.fr       */
>>>>>>> cylinder ok, shadow on cylinder debuged
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

<<<<<<< HEAD


void	tests(void)
{
	// char	*relative_path = "./pngegg.xpm";
	char	*relative_path = "./8081_earthmap2k1682441384.xpm";
	int			img_width;
	int			img_height;
	t_minirt	minirt;
	int			i;
	int			j;

	minirt.vars.mlx = mlx_init();
	minirt.vars.img = mlx_xpm_file_to_image(minirt.vars.mlx, relative_path, &img_width, &img_height);
	if (!minirt.vars.img)
		printf("problem with image reading\n");
	printf("width height %d %d\n", img_width, img_height);
	minirt.vars.win = mlx_new_window(minirt.vars.mlx, \
									img_width, img_height, "MINI RT");
	minirt.vars.addr = mlx_get_data_addr(minirt.vars.img, \
				&minirt.vars.bits_per_pixel, &minirt.vars.line_length, \
				&minirt.vars.endian);
	i = 0;
	while (i < img_width)
	{
		j = 0;
		while (j < img_height)
		{
			printf("address value %x \n", *(minirt.vars.addr + i + j * img_width));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(minirt.vars.mlx, minirt.vars.win, minirt.vars.img, 0, 0);
	mlx_loop(minirt.vars.mlx);
=======
void	tests(void)
{
	double	distance;
	t_plane	*plane;
	t_ray	ray;
	t_cam	cam;

	plane = malloc(sizeof(t_plane));
	plane->point = make_point(0, 0, -99);
	plane->normal = make_vect(0, 0, 1);
	ray.origin = make_point(0, 0, 0);
	ray.direct = make_vect(0, 0, -1);
	cam.origin = make_point(-50, 0, 0);
	cam.direction = point_subtract(cam.origin, plane->point);
	distance = ray_plane_distance(plane, ray);
	printf("distance btwn r & plane %f\n", distance);
	printf("cam direction dot normal %f\n", \
		vect_dot(cam.direction, plane->normal));
>>>>>>> cylinder ok, shadow on cylinder debuged
}
