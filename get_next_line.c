/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:43:38 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/24 12:42:04 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
	static size_t	index;
	char	*buffer;
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(150);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	index = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		res[i] = buffer[i];
		i++;
	}
	printf("%ld", index);
	printf("%s", res);
	return (res);
}
