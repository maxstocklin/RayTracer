/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:24:05 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/24 11:24:05 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
			count++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (count);
}

static int	ft_wordsize(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != 0 && s[i] != c)
	{
		count++;
		i++;
	}
	count--;
	return (count);
}

static char	*ft_create_word(char const *s, char c, int i)
{
	char	*dest;
	int		j;

	dest = (char *)malloc(sizeof(char) * (ft_wordsize(s, c, i) + 2));
	if (!dest)
		return (0);
	j = 0;
	while (s[i] != 0 && s[i] != c)
	{
		dest[j] = s[i];
		j++;
		i++;
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		count;

	i = 0;
	count = 0;
	dest = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!dest)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
		{
			dest[count] = ft_create_word(s, c, i);
			count++;
		}
		while (s[i] != c && s[i] != 0)
			i++;
	}
	dest[count] = 0;
	return (dest);
}

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

double	ft_atod(char *str)
{
	int		i;
	double	pos;
	double	res;
	int		dec;

	res = 0;
	pos = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pos *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
		res = (res * 10) + str[i++] - 48;
	dec = 1;
	if (str[i] == '.')
	{
		i++;
		while (str[i] <= '9' && str[i] >= '0')
		{
			res = (res * 10) + str[i] - 48;
			i++;
			dec *= 10;
		}
	}
	if (str[i] != 0)
	{
		printf("ERROR = %s\n", str);
		exit(1);
	}
	res = (res * pos) / (double)dec;
	return (res);
}
