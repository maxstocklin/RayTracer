/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rad_deg_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:28:35 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/18 18:21:02 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

double	rad_to_deg(double rad)
{
	return (180.0 / M_PI * rad);
}

double	deg_to_rad(double deg)
{
	return ((M_PI / 180.0) * deg);
}
