/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:07:08 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/07 18:18:37 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_errormessage()
{
	printf("USAGE:\n");
	printf("run the program with \"./minirt\" followed by the .rt file name.\n");
	printf("The .rt file must have least have a Camera and an ambiant light.\n");
	printf("You can add as many objects (spheres, cones, planes, and cylinders) as you want.\n");
	printf("You can add as many spotlights as you want.\n");
	printf("For all objects, you must specify their reflection coefficient.\n");
	printf("For spheres, you can specify the material:\n");
	printf("- checkerboard\n");
	printf("- bumpmap\n");
	printf("- transparent\n");
	printf("For planes, you can specify the material:\n");
	printf("- bumpmap\n");
}
int	ft_error(int index)
{
	if (index == 1)
		printf("Error: Please specify a file name\n");
	else if (index == 2)
		printf("Error: wrong RGB colors\n");
	else if (index == 3)
		printf("Error: wrong XYZ coordinates\n");
	else if (index == 4)
		printf("Error: wrong input\n");
	else if (index == 5)
		printf("Error: wrong XYZ vectors");
	else if (index == 6)
		printf("Error: Incorrect assignation\n");
	else if (index == 7)
		printf("Error: Failed to allocate memory\n");
	else if (index == 8)
		printf("Error: File not found\n");
	else if (index == 9)
		printf("Error: at least ambiant light and camera must be set\n");
	else if (index == 10)
		printf("Error: problem transparency\n");
	else if (index == 11)
		printf("Error: problem with image reading\n"); // todo: remodify
	ft_errormessage();
	exit (EXIT_FAILURE);
}
