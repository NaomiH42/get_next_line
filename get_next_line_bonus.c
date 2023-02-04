/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:49:08 by ehasalu           #+#    #+#             */
/*   Updated: 2023/02/04 13:51:04 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	size_t	i;
	size_t	len;
	char	*dest;

	len = ft_strlen(s);
	i = 0;
	dest = (char *)ft_calloc(sizeof(char), (len + 1));
	ft_memset(dest, 0, sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void trim(char **line)
{
	size_t	l;
	size_t	i;
	char	*trimmed;

	i = 0;
	l = 0;
	while ((*line)[i] != '\n' && (*line)[i])
		i++;
	if ((*line)[i] == '\n')
		i++;
	trimmed = (char *)ft_calloc(sizeof(char), (ft_strlen(*line) - i + 1));
	if (!trimmed)
		return;
	while ((*line)[i])
	{
		trimmed[l] = (*line)[i];
		i++;
		l++;
	}
	free(*line);
	*line = trimmed;
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
	if (line[i] == '\n')
		i++;
	ret = (char *)ft_calloc(sizeof(char), (i + 1));
	//ft_memset(ret, 0, sizeof(char) * (i + 2));
	while (l < i)
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
	char	*temp;

	line = ft_strdup("");
	line = ft_strjoin(line, *buffer);
	temp = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (ft_strchr(*buffer, '\n') == NULL)
	{
		bytes = read(fd ,temp, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(temp);
			if (ft_strlen(line) != 0)
				return(cut_extra(line));	
			free(line);
			return(NULL);
		}
		temp[bytes] = '\0';
		line = ft_strjoin(line, temp);
		if (buffer != NULL)
		{
			free(*buffer);
			*buffer = ft_strdup("");
		}
		*buffer = ft_strjoin(*buffer, temp);
	}
	free(temp);
	return (cut_extra(line));
}

char	*get_next_line(int fd)
{
	static char	*buf[2048];
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	if (!buf[fd])
	{
		buf[fd] = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));	
	}
	line = read_fd(&buf[fd], fd);
	trim(&buf[fd]);
	return (line);
}
