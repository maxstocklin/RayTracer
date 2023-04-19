#include "minirt.h"

int	ft_is_all_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (TRUE);
	return (FALSE);
}

int	ft_is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (TRUE);
	return (FALSE);
}

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
