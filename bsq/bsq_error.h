/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjeon <jchy1216@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 03:36:36 by chjeon            #+#    #+#             */
/*   Updated: 2026/08/16 03:43:47 by chjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_ERROR_H
# define BSQ_ERROR_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_map_info
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
}	t_map_info;

int		is_printable(char c);
int		validate_header(char *line, t_map_info *info);
int		validate_line(char *line, t_map_info *info, int current_row);
void	free_grid(char **grid, int allocated_rows);
int		print_map_error(char **grid, int allocated_rows);

#endif