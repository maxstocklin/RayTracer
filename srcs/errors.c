/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:07:08 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/24 11:07:32 by srapopor         ###   ########.fr       */
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
	exit (EXIT_FAILURE);
}
