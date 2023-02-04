/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:30:14 by ehasalu           #+#    #+#             */
/*   Updated: 2023/02/04 15:05:13 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>
#include <limits.h>
int	main(void)
{
	int	fd1;
	char	*l;
	
	
	fd1 = open("files/alternate_line_nl_with_nl", O_RDWR);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	l = get_next_line(fd1);
	printf("%s", l);
	free(l);
	close(fd1);
}
