/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 18:41:28 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/16 01:50:15 by sumlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

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

int	main(int argc, char **argv)
{
	
}
