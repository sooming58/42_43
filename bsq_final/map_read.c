/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:39:22 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 19:28:43 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>
#include <unistd.h>

char	*read_line(int fd)
{
	char	buf[500];
	char	c;
	char	*line;
	int		len;
	int		i;

	len = 0;
	while (read(fd, &c, 1) > 0 && c != '\n')
	{
		if (len < 499)
			buf[len++] = c;
	}
	if (len == 0 && c != '\n')
		return (NULL);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buf[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

int	check_line(char *line, t_map_info *info)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != info->empty && line[i] != info->obstacle)
			return (0);
		i++;
	}
	return (1);
}

char	**free_line(char **grid, char *temp, t_map_info *info, int i)
{
	if (!i)
		info->cols = ft_strlen(temp);
	else
	{
		if (ft_strlen(temp) != info->cols)
		{
			free(temp);
			return (free_grid(grid, i));
		}
	}
	if (check_line(temp, info) == 0)
	{
		free(temp);
		return (free_grid(grid, i));
	}
	return (grid);
}

char	**read_map(int fd, t_map_info *info)
{
	char	**grid;
	char	*temp;
	int		i;

	if (fd < 0 || !info || info->rows <= 0)
		return (NULL);
	grid = (char **)malloc(sizeof(char *) * info->rows);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < info->rows)
	{
		temp = read_line(fd);
		if (!temp)
			return (free_grid(grid, i));
		if (free_line(grid, temp, info, i) == NULL)
			return (NULL);
		grid[i] = temp;
		i++;
	}
	return (grid);
}
