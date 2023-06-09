/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:08:15 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/09 16:18:32 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int	loop_hook(t_minirt *minirt)
{
	if (minirt->recalc == 0)
	{
		new_draw_window(*minirt, 0, 0);
		minirt->recalc = 1;
	}
	return (0);
}

int	display_mlx_win(t_minirt *minirt)
{
	minirt->vars.mlx = mlx_init();
	if (minirt->vars.mlx != NULL)
	{
		minirt->vars.win = mlx_new_window(minirt->vars.mlx, \
		WIDTH, HEIGHT, "MINI RT");
		if (minirt->vars.win != NULL)
		{
			minirt->vars.img = mlx_new_image(minirt->vars.mlx, WIDTH, HEIGHT);
			if (minirt->vars.img != NULL)
			{
				minirt->vars.addr = mlx_get_data_addr(minirt->vars.img, \
				&minirt->vars.bits_per_pixel, &minirt->vars.line_length, \
				&minirt->vars.endian);
				mlx_put_image_to_window(minirt->vars.mlx, minirt->vars.win, \
				minirt->vars.img, 0, 0);
				add_mlx_hook(minirt);
				mlx_loop_hook(minirt->vars.mlx, loop_hook, minirt);
				mlx_loop(minirt->vars.mlx);
				return (0);
			}
		}
	}
	return (1);
}

char	**ft_parse_spaces(char *str)
{
	char	**dest;

	dest = ft_split_spaces(str);
	return (dest);
}

int	ft_checkinit(t_minirt *minirt, char *str)
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
		if (ft_is_all_whitespace(line) == FALSE)
		{
			tab = ft_parse_spaces(line);
			ft_assignment(minirt, tab);
			ft_free_array(tab);
		}
		free(line);
	}
	if (!minirt->ambiant || !minirt->camera)
		ft_error(9);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_minirt	minirt;

	if (ac != 2)
	{
		ft_error(1);
	}
	ft_set_null(&minirt);
	if (ft_checkinit(&minirt, av[1]) == FALSE)
	{
		exit(EXIT_FAILURE);
	}
	ft_print_ray(minirt);
	set_photon_map(&minirt, 0, 0);
	minirt.rt = 1;
	ft_set_map(&minirt);
	ft_set_bump(&minirt);
	display_mlx_win(&minirt);
	return (0);
}
