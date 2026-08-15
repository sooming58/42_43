/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:41:28 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 04:29:07 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	rewind_fileoffset(int fd, int len, int has_newline)
{
	if (has_newline)
		lseek(fd, -(ssize_t)(len + 1), SEEK_CUR);
	else
		lseek(fd, -(ssize_t)len, SEEK_CUR);
}

void	process_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "map error\n", 10);
		return ;
	}
	else
	{
		process_map(fd);
		close(fd);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		process_map(0);
	else
	{
		i = 1;
		while (argc > 1)
		{
			if (i > 1)
				write(1, "\n", 1);
			process_file(argv[i]);
			i++;
		}
	}
	return (0);
}
