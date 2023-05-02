/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:16:01 by mstockli          #+#    #+#             */
/*   Updated: 2023/05/02 11:58:39 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "mlx.h"
# include "../rt_helpers/helpers.h"
# include <sys/uio.h>

typedef struct s_ambiant
{
	double	intensity;
	t_rgb	rgb;
}				t_ambiant;

typedef struct s_cam
{
	t_point	origin;
	t_vect	direction;
	double	angle;
}				t_cam;

typedef struct s_light
{
	double			intensity;
	t_point			origin;
	t_rgb			rgb;
	int				index;
	struct s_light	*next;
}				t_light;

typedef struct s_sphere
{
	double			diameter;
	t_point			origin;
	t_rgb			rgb;
	int				index;
	struct s_sphere	*next;
	double 			reflect;
}				t_sphere;

typedef struct s_disc
{
	double			diameter;
	t_point			origin;
	t_vect			normal;
	t_rgb			rgb;
	int				index;
	double 			reflect;
	struct s_disc	*next;
}				t_disc;


typedef struct s_plane
{
	t_vect			normal;
	t_point			point;
	t_rgb			rgb;
	int				index;
	double 			reflect;
	struct s_plane	*next;

}				t_plane;

typedef struct s_cylinder
{
	t_vect				axis;
	t_point				origin;
	t_rgb				rgb;
	double				diameter;
	double				height;
	int					index;
	struct s_cylinder	*next;
	double				a;
	double				b;
	double				c;
	double 				reflect;

}				t_cylinder;

typedef struct s_cone {
	t_point			origin;
	t_vect			axis;
	t_rgb			rgb;
	double			angle;
	int				index;
	struct s_cone	*next;
	double			k;
	double			a;
	double			b;
	double			c;
	double 			reflect;

}	t_cone;

typedef struct s_vars
{
	void	*mlx;
	void	*win;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_vars;

typedef struct s_map{
	t_vars		texture;
	int			width;
	int			height;

}	t_map;
typedef struct s_minirt
{
	t_vars		vars;
	t_map		map;
	t_map		bump;
	t_cylinder	*cylinders;
	t_disc		*discs;
	t_plane		*planes;
	t_sphere	*spheres;
	t_cone		*cones;
	t_cam		*camera;
	t_light		*lights;
	t_ambiant	*ambiant;
	int			num_objects;
	int			num_spotlights;
	int			recalc;
	int			show_texture;
	int			show_checkboard;
	int			mirrorlvl;

	int			x;
	int			y;

}	t_minirt;

typedef struct s_intersection
{
	int		color;
	t_rgb	rgb;
	t_rgb	ambiant;
	t_rgb	diffuse;
	t_rgb	specular;
	t_rgb	object_color;
	t_rgb	reflection;
	double	distance;
	t_point	point;
	t_vect	normal;
	int		index;
}	t_intersect;

typedef struct s_screen
{
	t_point	top_left;
	t_point	center;
	t_vect	vup;
	t_vect	u;
	t_vect	v;
	t_vect	x_inc_vec;
	t_vect	y_inc_vec;
}	t_screen;

# define WIDTH 1400		/* horizonal window size		*/
# define HEIGHT 900 		/* vertical window size		*/

# define PHONG_POW 100
# define PHONG_COEF 0.9
# define MIRR_COEF 0.1
# define BOARD_SCALE 20

# define FALSE 1
# define TRUE 0
# define BUFFER_SIZE 42

/* EVENTS */
# define KEYPRESS 2
# define MOUSEPRESS 4
# define MOUSERELEASE 5
# define MOUSEMOVE 6
# define DESTROYNOTIFY 17

/* KEY HOOKS */
# define KEY_ESC 53
# define RETURN_KEY 36
# define TAB_KEY 48
# define SPACE_KEY 49

/* Zoom */
# define MINUS_KEY 27
# define PLUS_KEY 24

/* Move */
# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

/* MOUSE HOOKS */
# define LEFT_CLICK 1
# define SCROLLUP_KEY 4
# define SCROLLDOWN_KEY 5

/*		HOOKS		*/
void			add_mlx_hook(t_minirt *ray);

/*		ERRORS		*/
int				ft_error(int index);

/*		INIT		*/
void			ft_set_null(t_minirt *ray);
t_rgb			ft_get_rgb(char *str);
t_point			ft_get_xyz(char *str);
t_vect			ft_get_direction(char *str);

/*		CHECK		*/
int				ft_check_rgb(char *str);
int				ft_check_xyz(char *str);
int				ft_check_rgb_255(t_rgb rgb);
int				ft_check_xyz_int(t_point xyz);
int				ft_check_direction_int(t_vect xyz);

/*		SPLIT SPACES		*/
char			**ft_split_spaces(char const *s);
int				ft_is_all_whitespace(char *str);
int				ft_is_whitespace(char c);

/*		UTILS		*/
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
int				ft_strcmp(char *input, char *str);
double			ft_atod(char *str, double pos, double res, int dec);

/*		ASSIGMENT 1, 2 & 3		*/
void			ft_assignment(t_minirt *ray, char **tab);
double			ft_assign_angle(char *str);
double			ft_assign_diameter(char *str);
double			ft_assign_range(char *str);
int				check_array_size(char **tab, int size);
void			assign_sphere(t_minirt *minirt, char **tab);
void			assign_plane(t_minirt *minirt, char **tab);
void			assign_cylinder(t_minirt *minirt, char **tab);
void			assign_cone(t_minirt *minirt, char **tab);
void			assign_spotlight(t_minirt *minirt, char **tab);
void			assign_camera(t_minirt *minirt, char **tab);
void			assign_ambiant(t_minirt *minirt, char **tab);

/*		GNL		*/
char			*get_next_line(int fd);
char			*ft_strjoin(char *s1, char const *s2);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *str);

/*		FREE		*/
void			ft_free_array(char **tab);

/*		GET_INTERSECT		*/
int				get_color(t_minirt minirt, t_ray ray);
t_intersect		intersect_cylinders(t_minirt minirt, t_ray ray, \
	t_intersect intersect);
t_intersect		intersect_planes(t_minirt minirt, t_ray ray, t_intersect intersect);
t_intersect		intersect_cones(t_minirt minirt, t_ray ray, t_intersect intersect);
t_intersect		intersect_spheres(t_minirt minirt, t_ray ray, t_intersect intersect);


/*		APPLY_LIGHT		*/
int				apply_light(t_minirt minirt, t_intersect inter);
t_rgb			get_diffuse(t_minirt minirt, \
	t_intersect inter, double adjustment, int *check);
t_rgb			get_specular(t_minirt minirt, t_intersect inter, \
	double angle, double specular);

/*		CLOSEST_OBJECT		*/
int				closest_object(t_minirt minirt, t_ray lray);
void			closest_sphere(t_ray lray, t_sphere *spheres, \
	double *closest, int *index);
void			closest_plane(t_ray lray, t_plane *planes, double *closest, \
	int *index);
void			closest_cylinder(t_ray lray, t_cylinder *cylinder, \
	double *closest, int *index);
void			closest_cone(t_ray lray, t_cone *cone, double *closest, \
	int *index);

/*		SPHERE FUNCTIONS		*/
double			ray_sphere_distance(t_sphere *sphere, t_ray ray);
t_rgb			apply_map(double lat, double lng, t_minirt minirt);
t_rgb			apply_checkboard(double phi, double theta);
t_intersect		color_sphere(t_minirt minirt, t_sphere *sphere, \
	t_ray ray, t_intersect old_intersect);

/*		PLANE FUNCTIONS		*/
t_intersect		color_plane(t_minirt minirt, t_plane *plane, \
	t_ray ray, t_intersect old_intersect);
t_rgb			get_checkboard_plane(t_intersect inter, \
	t_plane *plane, t_ray ray);
double			ray_plane_distance(t_plane *plane, t_ray ray);

/*		CYLINDER FUNCTIONS		*/
t_intersect		color_cylinder(t_minirt minirt, t_cylinder *cylinder, \
	t_ray ray, t_intersect old_intersect);
t_vect			get_cylinder_norm(t_intersect intersection, \
	t_cylinder *cylinder);
double			ray_cylinder_distance(t_cylinder *cylinder, t_ray ray);
double			get_dist_cylinder(t_cylinder *cylinder, t_ray ray, \
	double t1, double t2);
double			check_height(t_cylinder *cylinder, t_ray ray, double t);

/*		CONE FUNCTIONS		*/
t_intersect		color_cone(t_minirt minirt, t_cone *cone, \
	t_ray ray, t_intersect old_intersect);
t_vect			get_cone_norm(t_intersect intersection, t_cone *cone);
double			ray_cone_distance(t_cone cone, t_ray ray);

/*		MAKE RAYS		*/
void			new_draw_window(t_minirt minirt, int i, int j);
t_intersect		apply_intersect(t_intersect new, t_intersect old, \
	t_minirt minirt);

/*		TO BE REMOVED		*/
void			ft_print_ray(t_minirt ray);
void			tests(void);





t_intersect	color_disc(t_minirt minirt, t_disc *disc, \
	t_ray ray, t_intersect old_intersect);
t_intersect	ray_disc_intersect(t_disc *disc, t_ray ray, \
	t_minirt minirt);
double	ray_disc_distance(t_disc *disc, t_ray ray);



#endif
