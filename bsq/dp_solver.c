/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:48:41 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 03:59:07 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>
#include <unistd.h>

int	min_three(int a, int b, int c)
{
	int	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

void	init_dp_row(char **grid, int *dp_row, t_map_info *info, int row)
{
	int	j;

	j = 0;
	while (j < info->cols)
	{
		if (grid[row][j] == info->obstacle)
			dp_row[j] = 0;
		else
			dp_row[j] = 1;
		j++;
	}
}

int	solve_bsq(char **grid, t_map_info *info, t_square *best)
{
	int	**dp;
	int	i;
	int	j;

	dp = (int **)malloc(sizeof(int *) * info->rows);
	i = 0;
	while (i < info->rows)
	{
		dp[i] = (int *)malloc(sizeof(int) * info->cols);
		init_dp_row(grid, dp[i], info, i);
		j = 0;
		while (i > 0 && j < info->cols)
		{
			if (grid[i][j] != info->obstacle)
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1],
						dp[i - 1][j - 1]) + 1;
			if (dp[i][j] > best->size)
				*best = (t_square){dp[i][j], i, j};
			j++;
		}
		i++;
	}
	return (dp);
}

void	fill_map(char **grid, t_map_info *info, t_square *best)
{
	int	i;
	int	j;

	i = best->row - best->size + 1;
	j = best->col - best->size + 1;
	while (i < best->row)
	{
		while (j < best->col)
		{
			grid[i][j] = info->full;
			j++;
		}
		i++;
	}
}

void	map_print(char **grid, t_map_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->rows)
	{
		while (j < info->cols)
		{
			write(1, &grid[i][j], 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}
