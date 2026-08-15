/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjeon <jchy1216@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 03:40:08 by chjeon            #+#    #+#             */
/*   Updated: 2026/08/16 03:43:59 by chjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_error.h"

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

void	free_grid(char **grid, int allocated_rows)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < allocated_rows)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

int	print_map_error(char **grid, int allocated_rows)
{
	free_grid(grid, allocated_rows);
	write(2, "map error\n", 10);
	return (0);
}
