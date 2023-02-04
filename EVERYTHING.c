
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:43:42 by ehasalu           #+#    #+#             */
/*   Updated: 2023/02/01 21:49:21 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*temp;
	size_t	test;

	if (nmemb == 0 || size == 0)
	{
		temp = malloc(0);
		return (temp);
	}
	test = nmemb * size;
	if (test / nmemb != size)
		return (NULL);
	temp = malloc(size * nmemb);
	if (!temp)
		return (NULL);
	ft_memset(temp, 0, size * nmemb);
	return (temp);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		res[i] = *s2;
		i++;
		s2++;
	}
	res[i] = '\0';
	free (s1);
	return (res);
}

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

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = 0;
//	i = ft_strlen(s);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
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

#include <stdio.h>
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
	trim(&buf[fd]);//ft_strrchr(buf[fd], '\n');
	return (line);
}

int	main(void)
{
	int	fd1;
	char	*l;
	
	
	fd1 = open("file.xt", O_RDWR);
//	get_next_line(fd1);
//	get_next_line(fd1);
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
