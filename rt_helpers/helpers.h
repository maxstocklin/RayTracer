/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:57:21 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/19 15:13:41 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H
# include	<math.h>
# include <string.h>
# include <stdio.h>
# include <assert.h>

typedef struct s_point
{
	double	x;
	double	y;
	double	z;

}	t_point;

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;

}	t_vect;

typedef struct s_ray
{
	t_point	origin;
	t_vect	direct;

}	t_ray;

typedef struct s_screen_size
{
	int	width;
	int	height;
}	t_screen_size;

double	vect_dot(t_vect vect1, t_vect vect2);
double	vect_length(t_vect vect);
double	vect_angle(t_vect vect1, t_vect vect2);
double	rad_to_deg(double rad);
double	deg_to_rad(double deg);
t_vect	vect_add(t_vect vect1, t_vect vect2);
t_vect	vect_subtract(t_vect vect1, t_vect vect2);
t_vect	vect_scale(t_vect vect, double scale);
t_point	point_offset_1(t_point point, t_vect vect);
t_vect	vect_cross(t_vect v1, t_vect v2);
t_point	make_point(double x, double y, double z);
t_vect	make_vect(double x, double y, double z);
void	make_rays(t_ray camera, t_screen_size screen);

#endif
