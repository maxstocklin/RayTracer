/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:15:19 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/26 11:44:03 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"



void	tests(void)
{
	// char	*relative_path = "./pngegg.png";
	char	*relative_path = "./pngegg.xpm";
	// char	*relative_path = "./8081_earthmap2k1682441384.xpm";

	int		img_width;
	int		img_height;
	t_minirt minirt;

	minirt.vars.mlx = mlx_init();
	minirt.vars.img = mlx_xpm_file_to_image(minirt.vars.mlx, relative_path, &img_width, &img_height);

	if (!minirt.vars.img)
		printf("problem with image reading\n");
	printf("width height %d %d\n", img_width, img_height);
	minirt.vars.win = mlx_new_window(minirt.vars.mlx,
									 img_width, img_height, "MINI RT");
	minirt.vars.addr = mlx_get_data_addr(minirt.vars.img, \
				&minirt.vars.bits_per_pixel, &minirt.vars.line_length, \
				&minirt.vars.endian);

	//mlx_put_image_to_window(minirt.vars.mlx, minirt.vars.win, minirt.vars.img, 0, 0);
}
