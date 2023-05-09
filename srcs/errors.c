/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:07:08 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/09 16:19:35 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_error(int index)
{
	if (index == 1)
		printf("Error: Please specify a file name\n");
	else if (index == 2)
		printf("Error: wrong RGB colors\n");
	else if (index == 3)
		printf("Error: wrong XYZ coordinates\n");
	else if (index == 5)
		printf("Error: wrong XYZ vectors\n");
	else if (index == 6)
		printf("Error: wrong input\n");
	else if (index == 7)
		printf("Error: Failed to allocate memory\n");
	else if (index == 8)
		printf("Error: File not found\n");
	else if (index == 9)
		printf("Error: at least ambiant light and camera must be set\n");
	else if (index == 10)
		printf("Error: problem transparency\n");
	else if (index == 11)
		printf("Error: problem with image reading\n");
	exit (EXIT_FAILURE);
}
