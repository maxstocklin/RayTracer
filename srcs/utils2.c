/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:24:05 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 17:21:39 by max              ###   ########.fr       */
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
