/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:05:18 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/09 15:36:46 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	res = ft_atod(str, 1, 0, 1);
	if (res < 0 || res > 1)
	{
		printf("Error: coefficient must be in range [0.0,1.0]\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}

double	ft_assign_diameter(char *str)
{
	double	res;

	res = ft_atod(str, 1, 0, 1);
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

	res = ft_atod(str, 1, 0, 1);
	if (res < 1 || res > 180)
	{
		printf("Error: Angle must be in range [0,180]\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}
