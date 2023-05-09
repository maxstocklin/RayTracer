/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:24:05 by srapopor          #+#    #+#             */
/*   Updated: 2023/05/09 15:25:12 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	pos;
	int	res;

	res = 0;
	pos = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pos *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	res = res * pos;
	return (res);
}

int	ft_strcmp(char *input, char *str)
{
	int	i;

	i = 0;
	if (!input)
		return (FALSE);
	while (str[i] && input[i])
	{
		if (str[i] != input[i])
			return (FALSE);
		i++;
	}
	if (str[i] != 0 || input[i] != 0)
		return (FALSE);
	return (TRUE);
}

double	ft_atod(char *str, double pos, double res, int dec)
{
	int		i;

	i = 0;
	if (str[i] == '-')
	{
		pos *= -1;
		if ((str[++i] > '9' || str[i] < '0') && str[i] != '.')
			ft_error(6);
	}
	while (str[i] <= '9' && str[i] >= '0')
		res = (res * 10) + str[i++] - 48;
	if (str[i] == '.')
	{
		if (str[++i] > '9' || str[i] < '0')
			ft_error(6);
		while (str[i] <= '9' && str[i] >= '0')
		{
			res = (res * 10) + str[i++] - 48;
			dec *= 10;
		}
	}
	if (str[i] != 0)
		ft_error(6);
	return ((res * pos) / (double)dec);
}
