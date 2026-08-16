/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:39:22 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 18:32:06 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>
#include <unistd.h>

/*
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
	(read_bytes = read(fd, &ch, 1));
	while ((read_bytes = read(fd, &ch, 1)) > 0 && ch != '\n')
		len++;
	if (!len || read_bytes <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	rewind_fileoffset(fd, len, (read_bytes > 0 && ch == '\n'));
	i = 0;
	while (i < len)
		read(fd, &line[i++], 1);
	if (read_bytes > 0 && ch == '\n')
		read(fd, &ch, 1);
	line[len] = '\0';
	return (line);
}
*/

/* 버퍼 공간이 부족할 때 기존 데이터를 복사하고 크기를 늘려주는 헬퍼 함수 */
static char	*ft_realloc(char *old, int old_len, int new_len)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * new_len);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < old_len)
		new_str[i] = old[i];
	free(old);
	return (new_str);
}

/* 1바이트씩 읽으면서 lseek 없이 한 줄을 모두 가져오는 함수 */
char	*read_line(int fd)
{
	char	*line;
	char	c;
	int		len;
	int		cap;

	len = 0;
	c = 0;
	cap = 128;
	line = (char *)malloc(cap);
	while (line && read(fd, &c, 1) > 0 && c != '\n')
	{
		if (len >= cap - 1)
		{
			line = ft_realloc(line, cap, cap * 2);
			cap *= 2;
		}
		if (line)
			line[len++] = c;
	}
	if (!line || (len == 0 && c != '\n'))
	{
		free(line);
		return (NULL);
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
