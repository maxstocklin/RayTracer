/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:24:17 by srapopor          #+#    #+#             */
/*   Updated: 2023/04/29 17:28:15 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	countwords(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (ft_is_whitespace(s[i]) == TRUE)
			i++;
		if (s[i] != 0)
			count++;
		while (ft_is_whitespace(s[i]) == FALSE && s[i] != 0)
			i++;
	}
	return (count);
}

static int	ft_wordsize(char const *s, int i)
{
	int	count;

	count = 0;
	while (s[i] != 0 && ft_is_whitespace(s[i]) == FALSE)
	{
		count++;
		i++;
	}
	count--;
	return (count);
}

static char	*ft_create_word(char const *s, int i)
{
	char	*dest;
	int		j;

	dest = (char *)malloc(sizeof(char) * (ft_wordsize(s, i) + 2));
	if (!dest)
		return (0);
	j = 0;
	while (s[i] != 0 && ft_is_whitespace(s[i]) == FALSE)
	{
		dest[j] = s[i];
		j++;
		i++;
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_split_spaces(char const *s)
{
	char	**dest;
	int		i;
	int		count;

	i = 0;
	count = 0;
	dest = (char **)malloc(sizeof(char *) * (countwords(s) + 1));
	if (!dest)
		return (0);
	while (s[i])
	{
		while (ft_is_whitespace(s[i]) == TRUE)
			i++;
		if (s[i] != 0)
		{
			dest[count] = ft_create_word(s, i);
			count++;
		}
		while (ft_is_whitespace(s[i]) == FALSE && s[i] != 0)
			i++;
	}
	dest[count] = 0;
	return (dest);
}
