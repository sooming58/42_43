/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 15:03:09 by chjeon            #+#    #+#             */
/*   Updated: 2026/08/16 19:33:10 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	validate_line(char *line, t_map_info *info, int current_row)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != info->empty && line[i] != info->obstacle)
			return (0);
		i++;
	}
	if (line[i] != '\n' || i == 0)
		return (0);
	if (current_row == 0)
		info->cols = i;
	else if (info->cols != i)
		return (0);
	return (1);
}

char	**free_grid(char **grid, int allocated_rows)
{
	int	i;

	if (!grid)
		return (NULL);
	i = 0;
	while (i < allocated_rows)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
	return (NULL);
}

void	process_map(int fd)
{
	t_map_info	info;
	t_square	best;
	char		**grid;
	char		*header;

	best = (t_square){0, 0, 0};
	header = read_line(fd);
	if (!header || !validate_header(header, &info))
	{
		free(header);
		write(2, "map error\n", 10);
		return ;
	}
	free(header);
	grid = read_map(fd, &info);
	if (!grid || !solve_bsq(grid, &info, &best))
	{
		free_grid(grid, info.rows);
		write(2, "map error\n", 10);
		return ;
	}
	fill_map(grid, &info, &best);
	map_print(grid, &info);
	free_grid(grid, info.rows);
}
