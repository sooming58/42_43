/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumlee <sumlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:47:51 by sumlee            #+#    #+#             */
/*   Updated: 2026/08/15 21:47:59 by sumlee           ###   ########.fr       */
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
