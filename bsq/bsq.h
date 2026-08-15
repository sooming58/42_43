/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:47:18 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 04:28:52 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_map_info
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
}t_map_info;

typedef struct s_square
{
	int	size;
	int	row;
	int	col;
}t_square;

// 외부 함수 선언
int		is_printable(char c);
int		validate_header(char *line, t_map_info *info);
int		ft_strlen(char *str);
void	rewind_fileoffset(int fd, int len, int has_newline);
void	process_file(char *filename);
char	*read_line(int fd);
char	**free_line(char **grid, char *temp, t_map_info *info, int i);
char	**read_map(int fd, t_map_info *info);
int		**solve_bsq(char **grid, t_map_info *info, t_square *best);


void	process_map(int fd, char **argv, t_map_info *info, t_square *best)
{
	t_map_info	info;
	t_square 	best;
	char	**grid;

	if (!validate_header(argv[0], &info))
	{
		write(2, "map error\n", 10);
		return ;
	}
	grid = read_map(fd, &info);
	if (!grid)
	{
		write(2, "map error\n", 10);
		return ;
	}
	if (!solve_bsq(grid, &info, &best))
	{
		free_grid(grid, info->rows);
		write(2, "map error\n", 10);
		return ;
	}
	fill_map(grid, info, best);
	map_print(grid, info);
	free_grid(grid, info->rows);
}

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
		return ;
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

#endif