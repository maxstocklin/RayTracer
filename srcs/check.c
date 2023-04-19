#include "minirt.h"

int	ft_check_rgb(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] != ',' && (str[i] < '0' || str[i] > '9'))
			return (FALSE);
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (FALSE);
	return (TRUE);
}

int	ft_check_xyz(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] != ',' && str[i] != '.' && str[i] != '-' \
		&& (str[i] < '0' || str[i] > '9'))
			return (FALSE);
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (FALSE);
	return (TRUE);
}

int	ft_check_rgb_255(t_rgb rgb)
{
	if (rgb.red < 0 || rgb.red > 255)
		return (FALSE);
	else if (rgb.green < 0 || rgb.green > 255)
		return (FALSE);
	else if (rgb.blue < 0 || rgb.blue > 255)
		return (FALSE);
	return (TRUE);
}

int	ft_check_xyz_int(t_point xyz)
{
	if (xyz.x < -10000 || xyz.x > 10000)
		return (FALSE);
	else if (xyz.y < -10000 || xyz.y > 10000)
		return (FALSE);
	else if (xyz.z < -10000 || xyz.z > 10000)
		return (FALSE);
	return (TRUE);
}

int	ft_check_direction_int(t_vect xyz)
{
    if (xyz.x < -1 || xyz.x > 1)
        return (FALSE);
    else if (xyz.y < -1 || xyz.y > 1)
        return (FALSE);
    else if (xyz.z < -1 || xyz.z > 1)
        return (FALSE);
    return (TRUE);
}
