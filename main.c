/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:49:40 by ehasalu           #+#    #+#             */
/*   Updated: 2023/02/06 18:27:48 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("file", O_RDONLY);

	int	i = 0;
	char *l = get_next_line(fd);

	while (i < 20)
	{
		printf("{%s}\n", l);
		free(l);
		l = get_next_line(fd);
		i++;
	}
	close(fd);
}

