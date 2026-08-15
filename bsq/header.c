/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 03:31:08 by chjeon            #+#    #+#             */
/*   Updated: 2026/08/16 03:59:15 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	is_printable(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

static int	check_header_chars(t_map_info *info)
{
	if (!is_printable(info->empty) || !is_printable(info->obstacle)
		|| !is_printable(info->full))
		return (0);
	if (info->empty == info->obstacle || info->obstacle == info->full
		|| info->empty == info->full)
		return (0);
	return (1);
}

static int	parse_rows(char *line, int num_len)
{
	int		i;
	long	rows;

	if (num_len <= 0)
		return (0);
	i = 0;
	rows = 0;
	while (i < num_len)
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		rows = rows * 10 + (line[i] - '0');
		if (rows > 2147483647)
			return (0);
		i++;
	}
	return ((int)rows);
}

int	validate_header(char *line, t_map_info *info)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] != '\n' || len < 4)
		return (0);
	info->full = line[len - 1];
	info->obstacle = line[len - 2];
	info->empty = line[len - 3];
	if (!check_header_chars(info))
		return (0);
	info->rows = parse_rows(line, len - 3);
	if (info->rows <= 0)
		return (0);
	return (1);
}
