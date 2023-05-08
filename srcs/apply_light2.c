/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:30:57 by max               #+#    #+#             */
/*   Updated: 2023/05/08 22:35:59 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"


double	get_dist(t_point t1, t_point t2)
{
	double	res;

	res = sqrt((t2.x - t1.x) * (t2.x - t1.x) + (t2.y -t1.y) \
		* (t2.y -t1.y) + (t2.z - t1.z) * (t2.z - t1.z));
	return (res);
}


t_rgb	sum_lightmax(t_rgb color1, t_rgb color2)
{
	t_rgb	sum;

	sum.red = color1.red + color2.red;
	sum.green = color1.green + color2.green;
	sum.blue = color1.blue + color2.blue;
	return (sum);
}

t_rgb	div_light(t_rgb color1, double count)
{
	t_rgb	sum;

	sum.red = color1.red / count;
	sum.green = color1.green / count;
	sum.blue = color1.blue / count;
	return (sum);
}


t_rgb	add_caustic(t_minirt minirt, t_intersect inter)
{
	double	dist;
	int		count = 0;
	double	weight;
	t_rgb	ccolor = make_color(0, 0, 0);
	int		total_photons = 0;

	while (minirt.photons)
	{
		total_photons++;
		if (minirt.photons->index == inter.index)
		{
			dist = get_dist(minirt.photons->point, inter.point);
			if (dist < (double)RADIUS)
			{
				weight = 1.0 - (dist / (double)RADIUS);


				ccolor = add_intensity(minirt.photons->color, weight);
				inter.caustic = sum_lightmax(inter.caustic, ccolor);
				count++;

		
				// printf(" dist = %f weight %f\n", dist, weight);
				// printf("pred %d pgreen %d pblue %d\n", minirt.photons->color.red, minirt.photons->color.green, minirt.photons->color.blue);
				// printf("ccred %d ccgreen %d ccblue %d\n", ccolor.red, ccolor.green, ccolor.blue);
				// printf("causred %d causgreen %d causblue %d\n", inter.caustic.red, inter.caustic.green, inter.caustic.blue);
			}
		}
		minirt.photons = minirt.photons->next;
	}

			// printf("total photons = %d\n", total_photons);

	if (count > 0)
	{
		inter.caustic = div_light(inter.caustic, count);
		// if (inter.caustic.red > 80)
		// 	printf("total_photons = %d count = %d red %d\n", total_photons, count, inter.caustic.red);

	}
	// printf("index = %d count = %d red %d\n", inter.index, count, inter.caustic.red);
	return (inter.caustic);
}



int	apply_light(t_minirt minirt, t_intersect inter)
{
	t_rgb	mixed;

	inter.caustic = add_intensity(inter.object_color, 0);
	inter.specular = add_intensity(inter.object_color, 0);
	inter.diffuse = add_intensity(inter.object_color, 0);

	if (inter.is_sphere == 1)
	{
		minirt.rt = 0;
		inter.exit_color = int_to_rgb(get_color(minirt, inter.exit));
	}
	else if (minirt.mirrorlvl == 0 && minirt.rt == 1)
		inter.caustic = add_caustic(minirt, inter);

	
	if (++minirt.mirrorlvl < MIRROR_LVL && inter.reflect > 0.01)
		inter.reflection = apply_reflection(minirt, inter);
	while (minirt.lights)
	{
		get_diff_and_specular(minirt, &inter);
		minirt.lights = minirt.lights->next;
	}
	if (minirt.mirrorlvl >= MIRROR_LVL || inter.reflect <= 0.01)
	{
		inter.rgb = sum_light3(inter.ambiant, inter.diffuse, inter.specular);
		if (inter.is_sphere == 1)
			inter.rgb = inter.exit_color; // sum_light(inter.rgb, inter.exit_color);
		else if (minirt.rt == 1)
			inter.rgb = sum_light(inter.rgb, inter.caustic);
		return (rgb_to_int(inter.rgb));
	}
	inter.rgb = sum_light(inter.ambiant, inter.diffuse);
	if (inter.is_sphere == 1)
		inter.rgb = inter.exit_color; // sum_light(inter.rgb, inter.exit_color);
	mixed = get_mirrors(inter.reflection, inter.rgb, inter.specular, inter);
	return (rgb_to_int(mixed));
}


// int	apply_light(t_minirt minirt, t_intersect inter)
// {
// 	t_rgb	mixed;

// 	inter.specular = add_intensity(inter.object_color, 0);
// 	inter.diffuse = add_intensity(inter.object_color, 0);
// 	// inter.caustic = add_intensity(inter.object_color, 0);
	
// 	if (inter.is_sphere == 1)
// 	{
// 		inter.exit_color = int_to_rgb(get_color(minirt, inter.exit));
// 	}
// 	// else
// 	// 	inter.caustic = add_caustic(minirt, inter);
// 	if (++minirt.mirrorlvl < 3 && inter.reflect > 0.01)
// 		inter.reflection = apply_reflection(minirt, inter);
// 	while (minirt.lights)
// 	{
// 		get_diff_and_specular(minirt, &inter);
// 		minirt.lights = minirt.lights->next;
// 	}
// 	if (minirt.mirrorlvl >= 3 || inter.reflect <= 0.01)
// 	{
// 		inter.rgb = sum_light3(inter.ambiant, inter.diffuse, inter.specular);
// 		if (inter.is_sphere == 1)
// 			inter.rgb = inter.exit_color; //sum_light(inter.rgb, inter.exit_color);
// 		return (rgb_to_int(inter.rgb));
// 	}
// 	inter.rgb = sum_light(inter.ambiant, inter.diffuse);
// 	if (inter.is_sphere == 1)
// 		inter.rgb = inter.exit_color; //sum_light(inter.rgb, inter.exit_color);
// 	mixed = get_mirrors(inter.reflection, inter.rgb, inter.specular, inter);
// 	return (rgb_to_int(mixed));
// }
