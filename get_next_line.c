/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:49:08 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/25 18:42:56 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim(char *line)
{
	size_t	l;
	size_t	i;
	char	*trimmed;

	i = 0;
	l = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	trimmed = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	ft_memset(trimmed, 0, sizeof(char) * (ft_strlen(line) - i));
	if (!trimmed)
		return (line);
	while (line[i])
	{
		trimmed[l] = line[i];
		i++;
		l++;
	}
	free(line);
	return (trimmed);
}

char	*cut_extra(char *line)
{
	char	*ret;
	size_t	i;
	size_t	l;

	l = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 2));
	ft_memset(ret, 0, sizeof(char) * (i + 2));
	while (l <= i)
	{
		ret[l] = line[l];
		l++;
	}
	ret[l] = '\0';
	free(line);
	return (ret);
}

char	*read_fd(char **buffer, int fd)
{
	int	bytes;
	char	*line;

	line = ft_strdup("");
	line = ft_strjoin(line, *buffer);
	line = trim(line);
	bytes = read(fd ,*buffer, BUFFER_SIZE);
	while (ft_strchr(*buffer, '\n') == NULL && bytes >= 0)
	{
		line = ft_strjoin(line, *buffer);
		bytes = read(fd ,*buffer, BUFFER_SIZE);
	}		
	line = ft_strjoin(line, *buffer);
	if (bytes <= 0)
		*buffer = line;
	return (cut_extra(line));
}

char	*get_next_line(int fd)
{
	static char	*buf[2048];
	char	*line;
	
	if (!buf[fd])
	{
		buf[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));	
		ft_memset(buf[fd], 0, (sizeof(char) * (BUFFER_SIZE + 1)));
	}
	line = read_fd(&buf[fd], fd);
	return (line);
	
}
