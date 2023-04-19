#include "minirt.h"
#include "mlx.h"

int	display_mlx_win(t_ray *ray)
{
	ray->vars.mlx = mlx_init();
	if (ray->vars.mlx != NULL)
	{
		ray->vars.win = mlx_new_window(ray->vars.mlx, \
		XMAX, YMAX, "MINI RT");
		if (ray->vars.win != NULL)
		{
			ray->vars.img = mlx_new_image(ray->vars.mlx, XMAX, YMAX);
			if (ray->vars.img != NULL)
			{
				ray->vars.addr = mlx_get_data_addr(ray->vars.img, \
				&ray->vars.bits_per_pixel, &ray->vars.line_length, \
				&ray->vars.endian);
				mlx_put_image_to_window(ray->vars.mlx, ray->vars.win, \
				ray->vars.img, 0, 0);
				add_mlx_hook(ray);
				mlx_loop(ray->vars.mlx);
				return (0);
			}
		}
	}
	return (1);
}

char	**ft_parse_spaces(char *str)
{
	int		i;
	char	**dest;

	dest = ft_split_spaces(str);
	return (dest);
}

int	ft_checkinit(t_ray *ray, char *str)
{
	char	**tab;
	char	*line;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_error(8);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_is_all_whitespace(line) == TRUE)
		{
			tab = ft_parse_spaces(line);
			ft_assignment(ray, tab);
			ft_free_array(tab);
		}
		free(line);
	}
	if (!ray->ambiant || !ray->camera)
		ft_error(9);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_ray	ray;

	if (ac != 2)
	{
		ft_error(1);
	}
	ft_set_null(&ray);
	if (ft_checkinit(&ray, av[1]) == FALSE)
	{
		exit(EXIT_FAILURE);
	}
	ft_print_ray(ray);
	//display_mlx_win(&ray);
	return (0);
}
