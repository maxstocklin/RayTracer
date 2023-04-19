/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:16:01 by mstockli          #+#    #+#             */
/*   Updated: 2023/04/19 12:08:41 by srapopor         ###   ########.fr       */
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

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

// typedef struct s_vect
// {
// 	double	x;
// 	double	y;
// 	double	z;
// }				t_vect;

// typedef struct s_point
// {
// 	double	x;
// 	double	y;
// 	double	z;
// }				t_point;

typedef struct s_ambiant
{
	double	intensity;
	t_rgb	rgb;

}				t_ambiant;

typedef struct s_light
{
	double			intensity;
	t_point			origin;
	t_rgb			rgb;
	struct s_light	*next;
}				t_light;

typedef struct s_cam
{
	t_point	origin;
	t_vect	direction;
	double	angle;
}				t_cam;

typedef struct s_sphere
{
	double			diameter;
	t_point			origin;
	t_rgb			rgb;
	struct s_sphere	*next;
}				t_sphere;

typedef struct s_plane
{
	t_vect			normal;
	t_point			point;
	t_rgb			rgb;
	struct s_plane	*next;

}				t_plane;

typedef struct s_cylinder
{
	t_vect				normal;
	t_point				origin;
	t_rgb				rgb;
	double				diameter;
	double				height;
	struct s_cylinder	*next;

}				t_cylinder;

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

typedef struct s_minirt
{
	t_vars		vars;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_sphere	*spheres;
	t_cam		*camera;
	t_light		*lights;
	t_ambiant	*ambiant;
}				t_minirt;

# define XMAX 900		/* horizonal window size		*/
# define YMAX 900 		/* vertical window size		*/

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
void	add_mlx_hook(t_minirt *ray);

/*		ERRORS		*/
int		ft_error(int index);

/*		INIT		*/
void	ft_set_null(t_minirt *ray);
t_rgb	ft_get_rgb(char *str);
t_point	ft_get_xyz(char *str);
t_vect	ft_get_direction(char *str);

/*		CHECK		*/
int		ft_check_rgb(char *str);
int		ft_check_xyz(char *str);
int		ft_check_rgb_255(t_rgb rgb);
int		ft_check_xyz_int(t_point xyz);
int		ft_check_direction_int(t_vect xyz);

/*		SPLIT SPACES		*/
char	**ft_split_spaces(char const *s);
int		ft_is_all_whitespace(char *str);
int		ft_is_whitespace(char c);

/*		UTILS		*/
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_strcmp(char *input, char *str);
double	ft_atod(char *str);

/*		ASSIGMENT		*/
void	ft_assignment(t_minirt *ray, char **tab);

/*		GNL		*/
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);


/*		FREE		*/
void	ft_free_array(char **tab);


/*		TO BE REMOVED		*/
void	ft_print_ray(t_minirt ray);

#endif
