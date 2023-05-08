/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:19:48 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/05 18:04:09 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_set_map(t_minirt *minirt)
{
	char	*relative_path;

	relative_path = "8081_earthmap2k.xpm";
	minirt->map.texture.mlx = mlx_init();
	minirt->map.texture.img = mlx_xpm_file_to_image(minirt->map.texture.mlx, \
		relative_path, &minirt->map.width, &minirt->map.height);
	printf("map width height %d %d\n", minirt->map.width, minirt->map.height);
	if (!minirt->map.texture.img)
		ft_error(10);
	minirt->map.texture.addr = mlx_get_data_addr(minirt->map.texture.img, \
		&minirt->map.texture.bits_per_pixel, &minirt->map.texture.line_length, \
				&minirt->map.texture.endian);
}

void	ft_set_bump(t_minirt *minirt)
{
	char	*relative_path;

	relative_path = "./8081_earthbump2k.xpm";
	minirt->bump.texture.mlx = mlx_init();
	minirt->bump.texture.img = mlx_xpm_file_to_image(minirt->bump.texture.mlx, \
		relative_path, &minirt->bump.width, &minirt->bump.height);
	printf("bump width height %d %d\n", minirt->bump.width, minirt->bump.height);
	if (!minirt->bump.texture.img)
		printf("problem with image reading\n");
	minirt->bump.texture.addr = mlx_get_data_addr(minirt->bump.texture.img, \
	&minirt->bump.texture.bits_per_pixel, &minirt->bump.texture.line_length, \
	&minirt->bump.texture.endian);
}
