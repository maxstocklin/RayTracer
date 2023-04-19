/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:53:53 by mstockli          #+#    #+#             */
/*   Updated: 2022/10/31 18:32:32 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*get_backup(char *line)
{
	static char	*res;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i] || !line[i + 1])
		return (free(line), NULL);
	if (line[i])
		i++;
	res = malloc(sizeof(char) * (1 + ft_strlen(line + i)));
	if (!res)
		return (0);
	while (line[i])
		res[j++] = line[i++];
	res[j] = 0;
	free(line);
	return (res);
}

static char	*get_line(char *line)
{
	char	*res;
	int		i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	res = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!res)
		return (0);
	i = 0;
	while (line[i])
	{
		res[i] = line[i];
		i++;
		if (line[i - 1] == '\n')
			break ;
	}
	res[i] = 0;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*line;
	char		*buf;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 1;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (read_bytes != 0 && ft_strchr(backup, '\n') == NULL)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buf[read_bytes] = 0;
		backup = ft_strjoin(backup, buf);
	}
	free(buf);
	line = get_line(backup);
	backup = get_backup(backup);
	return (line);
}
