/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 23:46:49 by chjeon            #+#    #+#             */
/*   Updated: 2026/08/16 18:32:40 by sumlee           ###   ########.fr       */
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

int		is_printable(char c);
int		validate_header(char *line, t_map_info *info);
int		ft_strlen(char *str);
//void	rewind_fileoffset(int fd, int len, int has_newline);
void	process_file(char *filename);
char	*read_line(int fd);
char	**free_line(char **grid, char *temp, t_map_info *info, int i);
char	**read_map(int fd, t_map_info *info);
int		**solve_bsq(char **grid, t_map_info *info, t_square *best);
void	fill_map(char **grid, t_map_info *info, t_square *best);
void	map_print(char **grid, t_map_info *info);
int		validate_line(char *line, t_map_info *info, int current_row);
char	**free_grid(char **grid, int allocated_rows);
void	process_map(int fd);

#endif
