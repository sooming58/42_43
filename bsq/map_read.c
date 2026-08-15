/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:39:22 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 01:49:06 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>

int		ft_strlen(char *str);
void	rewind_fileoffset(int fd, int len, int has_newline);

char	*read_line(int fd)
{
	char	*line;
	char	ch;
	ssize_t	read_bytes;
	int		len;
	int		i;

	if (fd < 0)
		return (NULL);
	len = 0;
	read_bytes = read(fd, &ch, 1);
	while (read_bytes > 0 && ch != '\n')
		len++;
	if (!len || read_bytes <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	rewind_offset(fd, len, (read_bytes > 0 && ch == '\n'));
	i = 0;
	while (i < len)
		read(fd, &line[i++], 1);
	if (read_bytes > 0 && ch == '\n')
		read(fd, &ch, 1);
	line[len] = '\0';
	return (line);
}

char	**free_grid(char **grid, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
	return (NULL);
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
	if (!check_line(temp, info))
	{
		free(temp);
		return (free_grid(grid, i));
	}
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
		free_line(grid, temp, info, i);
		grid[i] = temp;
		i++;
	}
	return (grid);
}
