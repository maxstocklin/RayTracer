/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:30:57 by max               #+#    #+#             */
/*   Updated: 2023/05/09 17:59:20 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

t_rgb	add_caustic(t_minirt minirt, t_intersect inter)
{
	double	dist;
	int		count;

	count = 0;
	while (minirt.photons)
	{
		if (minirt.photons->index == inter.index)
		{
			dist = get_dist(minirt.photons->point, inter.point);
			if (dist < (double)RADIUS)
			{
				count++;
				if (count > 254)
					break ;
			}
		}
		minirt.photons = minirt.photons->next;
	}
	inter.caustic.red = (int)((double)(count));
	inter.caustic.green = (int)((double)(count));
	inter.caustic.blue = (int)((double)(count));
	return (inter.caustic);
}

int	apply_basic(t_minirt minirt, t_intersect inter)
{
	inter.rgb = sum_light3(inter.ambiant, inter.diffuse, inter.specular);
	if (inter.is_sphere == 1)
		inter.rgb = sum_light(inter.specular, inter.exit_color);
	else if (minirt.rt == 1)
		inter.rgb = sum_light(inter.rgb, inter.caustic);
	return (rgb_to_int(inter.rgb));
}

int	apply_light(t_minirt minirt, t_intersect inter)
{
	t_rgb	mixed;

	if (inter.is_sphere == 1)
	{
		minirt.rt = 0;
		inter.exit_color = int_to_rgb(get_color(minirt, inter.exit));
	}
	else if (minirt.mirrorlvl == 0 && minirt.rt == 1 && inter.is_sphere == 2)
		inter.caustic = add_caustic(minirt, inter);
	if (++minirt.mirrorlvl < MIRROR_LVL && inter.reflect > 0.01)
		inter.reflection = apply_reflection(minirt, inter);
	get_diff_and_specular(minirt, &inter);
	if (minirt.mirrorlvl >= MIRROR_LVL || inter.reflect <= 0.01)
		return (apply_basic(minirt, inter));
	inter.rgb = sum_light(inter.ambiant, inter.diffuse);
	if (inter.is_sphere == 1)
		inter.rgb = sum_light(inter.specular, inter.exit_color);
	mixed = get_mirrors(inter.reflection, inter.rgb, inter.specular, inter);
	if (inter.is_sphere == 2)
		mixed = sum_light(inter.caustic, mixed);
	return (rgb_to_int(mixed));
}
