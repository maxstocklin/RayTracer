#include "minirt.h"

int	check_array_size(char **tab, int size)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (i != size)
		return (FALSE);
	return (TRUE);
}

double	ft_assign_range(char *str)
{
	double	res;

	res = ft_atod(str);
	if (res < 0 || res > 1)
	{
		printf("Error: light ratio must be in range [0.0,1.0]\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}

double	ft_assign_diameter(char *str)
{
	double	res;

	res = ft_atod(str);
	if (res < 0 || res > 1000)
	{
		printf("Error: light ratio must be in range [0,1000]\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}

double	ft_assign_angle(char *str)
{
	double	res;

	res = ft_atod(str);
	if (res < 0 || res > 180)
	{
		printf("Error: Angle must be in range [0,180]\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}

void	assign_ambiant(t_minirt *minirt, char **tab)
{
	t_ambiant	*ambiant;

	if (minirt->ambiant)
	{
		printf("Error: ambiant light can't be initialized twice\n");
		exit(EXIT_FAILURE);
	}
	if (check_array_size(tab, 3) == FALSE)
		ft_error(6);
	ambiant = malloc(sizeof(t_ambiant));
	if (!ambiant)
		ft_error(7);
	ambiant->intensity = ft_assign_range(tab[1]);
	ambiant->rgb = ft_get_rgb(tab[2]);
	minirt->ambiant = ambiant;
}

void	assign_camera(t_minirt *minirt, char **tab)
{
	t_cam	*camera;

	if (minirt->camera)
	{
		printf("Error: camera light can't be initialized twice\n");
		exit(EXIT_FAILURE);
	}
	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	camera = malloc(sizeof(t_cam));
	if (!camera)
		ft_error(7);
	camera->origin = ft_get_xyz(tab[1]);
	camera->direction = ft_get_direction(tab[2]);
	camera->angle = ft_assign_angle(tab[3]);
	minirt->camera = camera;
}

void	assign_spotlight(t_minirt *minirt, char **tab)
{
	t_light	*current;
	t_light	*light;

	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	light = malloc(sizeof(t_light));
	if (!light)
		ft_error(7);
	light->origin = ft_get_xyz(tab[1]);
	light->intensity = ft_assign_range(tab[2]);
	light->rgb = ft_get_rgb(tab[3]);
	light->next = NULL;
	current = minirt->lights;
	if (!current)
		minirt->lights = light;
	else
	{
		while (current->next)
		{
			current = current->next;
		}
		light->index = ++minirt->num_spotlights;
		current->next = light;
	}
}

void	assign_sphere(t_minirt *minirt, char **tab)
{
	t_sphere	*sphere;
	t_sphere	*current;

	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(7);
	sphere->origin = ft_get_xyz(tab[1]);
	sphere->diameter = ft_assign_diameter(tab[2]);
	sphere->rgb = ft_get_rgb(tab[3]);
	sphere->next = NULL;
	current = minirt->spheres;
	sphere->index = ++minirt->num_objects;
	if (!current)
		minirt->spheres = sphere;
	else
	{
		while (current->next)
			current = current->next;
		current->next = sphere;
	}
}

void	assign_plane(t_minirt *minirt, char **tab)
{
	t_plane	*plane;
	t_plane	*current;

	if (check_array_size(tab, 4) == FALSE)
		ft_error(6);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		ft_error(7);
	plane->point = ft_get_xyz(tab[1]);
	plane->normal = ft_get_direction(tab[2]);
	plane->rgb = ft_get_rgb(tab[3]);
	plane->next = NULL;
	current = minirt->planes;
	if (!current)
		minirt->planes = plane;
	else
	{
		while (current->next)
			current = current->next;
		plane->index = ++minirt->num_objects;
		current->next = plane;
	}
}

void	assign_cylinder(t_minirt *minirt, char **tab)
{
	t_cylinder	*cylinder;
	t_cylinder	*current;

	if (check_array_size(tab, 6) == FALSE)
		ft_error(6);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		ft_error(7);
	cylinder->origin = ft_get_xyz(tab[1]);
	cylinder->normal = ft_get_direction(tab[2]);
	cylinder->diameter = ft_assign_diameter(tab[3]);
	cylinder->height = ft_assign_diameter(tab[4]);
	cylinder->rgb = ft_get_rgb(tab[5]);
	cylinder->next = NULL;
	current = minirt->cylinders;
	if (!current)
		minirt->cylinders = cylinder;
	else
	{
		while (current->next)
			current = current->next;
		cylinder->index = ++minirt->num_objects;
		current->next = cylinder;
	}
}

void	ft_assignment(t_minirt *minirt, char **tab)
{
	if (ft_strcmp(tab[0], "A") == TRUE)
		assign_ambiant(minirt, tab);
	else if (ft_strcmp(tab[0], "C") == TRUE)
		assign_camera(minirt, tab);
	else if (ft_strcmp(tab[0], "L") == TRUE)
		assign_spotlight(minirt, tab);
	else if (ft_strcmp(tab[0], "sp") == TRUE)
		assign_sphere(minirt, tab);
	else if (ft_strcmp(tab[0], "pl") == TRUE)
		assign_plane(minirt, tab);
	else if (ft_strcmp(tab[0], "cy") == TRUE)
		assign_cylinder(minirt, tab);
	else
		ft_error(4);
}
