/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:30:57 by max               #+#    #+#             */
/*   Updated: 2023/05/03 16:47:40 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int	apply_light(t_minirt minirt, t_intersect inter)
{
	t_rgb	mixed;

	inter.specular = add_intensity(inter.object_color, 0);
	inter.diffuse = add_intensity(inter.object_color, 0);
	if (inter.is_sphere == 1)
		inter.exit_color = int_to_rgb(get_color(minirt, inter.exit));
	if (++minirt.mirrorlvl < 0 && inter.reflect > 0.01)
		inter.reflection = apply_reflection(minirt, inter);
	while (minirt.lights)
	{
		get_diff_and_specular(minirt, &inter);
		minirt.lights = minirt.lights->next;
	}
	if (minirt.mirrorlvl >= 0 || inter.reflect <= 0.01)
	{
		inter.rgb = sum_light3(inter.ambiant, inter.diffuse, inter.specular);
		if (inter.is_sphere == 1)
			inter.rgb = sum_light(inter.rgb, inter.exit_color);
		return (rgb_to_int(inter.rgb));
	}
	inter.rgb = sum_light(inter.ambiant, inter.diffuse);
	if (inter.is_sphere == 1)
		inter.rgb = sum_light(inter.rgb, inter.exit_color);
	mixed = get_mirrors(inter.reflection, inter.rgb, inter.specular, inter);
	return (rgb_to_int(mixed));
}
