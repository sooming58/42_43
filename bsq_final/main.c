/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 04:31:13 by chjeon            #+#    #+#             */
/*   Updated: 2026/08/16 20:19:08 by sumlee           ###   ########.fr       */
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

void	process_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "map error\n", 10);
		return ;
	}
	process_map(fd);
	close(fd);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		process_map(0);
	else
	{
		i = 1;
		while (argc > i)
		{
			if (i > 1)
				write(1, "\n", 1);
			process_file(argv[i]);
			i++;
		}
	}
	return (0);
}
