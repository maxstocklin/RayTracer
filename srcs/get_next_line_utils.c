/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:54:12 by mstockli          #+#    #+#             */
/*   Updated: 2022/10/31 18:32:33 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_zero(const char *s)
{
	char	*new;

	new = malloc(sizeof (char));
	if (new == NULL)
		return (NULL);
	new[0] = s[0];
	return (new);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!dest)
		return (0);
	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_zero("\0");
	if (s1)
	{
		while (s1[j])
		{
			dest[j] = s1[j];
			j++;
		}
	}
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s1;

	i = 0;
	if (!s)
		return (NULL);
	s1 = (char *)s;
	while (s1[i])
	{
		if (s1[i] == (char)c)
			return (&s1[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&s1[i]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
