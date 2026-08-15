/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:48:41 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/15 23:31:22 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>

int	min_three(int a, int b, int c)
{

}

int	update_dp_cell(int **dp, int i, int j, char cell_val, t_map_info *info)
{

}

void	row_zero(char **grid, char *dp, t_map_info *info, t_square *best)
{
	int	j;

	j = 0;
	while (j < info->cols)
	{
		if (grid[0][j] == info->obstacle)
			dp[j] = 0;
		else	
		{
			dp[j] = 1;
			if (!best->size)
			{
				best->size = 1;
				best->row = i;
				best->col = j;
			}
		}
		j++;
	}
}

void	col_zero(char **grid, char *dp, t_map_info *info, t_square *best)
{

}

void	solve_bsq(char **grid, t_map_info *info, t_square *best)
{
	int	**dp;
	int	i;
	int	j;

	dp = (int **)malloc(sizeof(int *) * info->rows);
	dp[0] = (int *)malloc(sizeof(int) * info->cols);
	row_zero(grid, dp[0], info, best);
	i = 1;
	while (i < info->rows)
	{
		dp[i] = (int *)malloc(sizeof(int) * info->cols);
		
	}
}
