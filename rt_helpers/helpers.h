/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:57:21 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/08 20:22:09 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <assert.h>

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;

}	t_point;

typedef struct s_photon{
	t_point			point;
	t_rgb			color;
	int				index;
	double			dist;
	struct s_photon	*next;

}	t_photon;

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

typedef struct s_intersection
{
	int			color;
	t_rgb		rgb;
	t_rgb		ambiant;
	t_rgb		diffuse;
	t_rgb		specular;
	t_rgb		object_color;
	t_rgb		reflection;
	t_rgb		caustic;
	double		distance;
	double		reflect;
	t_point		point;
	t_vect		normal;
	t_ray		exit;
	int			is_sphere;
	t_rgb		exit_color;
	int			index;
	t_photon	*photons;

}	t_intersect;

double	vect_dot(t_vect vect1, t_vect vect2);
double	vect_length(t_vect vect);
double	vect_angle(t_vect vect1, t_vect vect2);
double	rad_to_deg(double rad);
double	deg_to_rad(double deg);
t_vect	vect_add(t_vect vect1, t_vect vect2);
t_vect	point_subtract(t_point p1, t_point p2);
t_vect	vect_scale(t_vect vect, double scale);
t_point	point_offset_1(t_point point, t_vect vect);
t_vect	vect_cross(t_vect v1, t_vect v2);
t_point	make_point(double x, double y, double z);
t_vect	make_vect(double x, double y, double z);
void	make_rays(t_ray camera, t_screen_size screen);
int		rgb_to_int(t_rgb rgb);
t_rgb	int_to_rgb(unsigned int x);
t_rgb	sum_light(t_rgb color1, t_rgb color2);
t_rgb	add_light(t_rgb color1, t_rgb color2, double intensity);
t_rgb	add_intensity(t_rgb rgb, double intensity);
t_point	get_intersect(t_ray ray, double distance);
t_vect	vector_normalize(t_vect old);
t_point	point_add(t_point p1, t_point p2);
t_point	vect_to_point(t_vect v);
t_point	point_apply_2vect(t_point origin, t_vect u, t_vect v);
t_rgb	sum_light3(t_rgb color1, t_rgb color2, t_rgb color3);
t_rgb	make_color(int r, int g, int b);
t_vect	refract_vector(t_vect incident, t_vect normal, \
					double n1, double n2);

#endif
