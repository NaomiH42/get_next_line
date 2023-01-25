/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:30:14 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/25 16:02:50 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int	fd1;

	fd1 = open("text.txt", O_RDONLY);
	get_next_line(fd1);
}
