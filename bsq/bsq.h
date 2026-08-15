/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:47:18 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 03:44:42 by sumlee           ###   ########.fr       */
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
int		ft_strlen(char *str);
void	rewind_fileoffset(int fd, int len, int has_newline);
void	process_file(char *filename);
char	*read_line(int fd);
char	**free_grid(char **grid, int cnt);
int	check_line(char *line, t_map_info *info);
char	**free_line(char **grid, char *temp, t_map_info *info, int i);
char	**read_map(int fd, t_map_info *info);
int	solve_bsq(char **grid, t_map_info *info, t_square *best);


void	process_map(int fd)
{
	t_map_info	info;
	t_square 	best;
	char	**grid;

	if (!parse_header(fd, &info))
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
		free_map(grid, &info);
		write(2, "map error\n", 10);
		return ;
	}
	fill_print(grid, &info, &best);
	free_map(grid, &info);
}

#endif