/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:43:38 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/24 16:47:50 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	is_nl(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i != size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*res;
	size_t	l;

	l = 0;
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	while (s1[l])
	{
		res[i] = s1[l];
		i++;
		l++;
	}
	l = 0;
	while (s2[l])
	{
		res[i] = s2[l];
		i++;
		l++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_result(char *copy)
{
	size_t	i;
	char	*result;
	size_t	len;

	i = 0;
	len = 0;
	while(copy[len] != '\n' && copy[len])
		len++;
	result = (char *)malloc(sizeof(char) * (len + 2));
	while(i <= len)
	{
		result[i] = copy[i];
		i++;
	}
	free(copy);
	return (result);
}
char	*trim_side(char *buf, int side)
{
	size_t	i;
	size_t	l;
	char	*ret;

	ret = NULL;
	l = 0;
	i = 0;
	if (side == 0)
	{
		while (buf[i] != '\n')
			i++;
		ret = (char *)malloc(sizeof(char) * (ft_strlen(buf) - i + 1));
		while (buf[i])
		{
			ret[l] = buf[i];
			i++;
			l++;
		}
	}
	else
	{
		while (buf[i] != '\n')
			i++;
		ret = (char *)malloc(sizeof(char) * (i + 1));
		i = 0;
		while (buf[i] != '\n')
		{
			ret[l] = buf[i];
			i++;
			l++;
		}
	}
	ret[l] = '\0';
	return (ret);
}

#include <stdio.h>
char *get_next_line(int fd)
{
	size_t index;
	static char	*buffer;
	char	*res;
	static int	flag;

	if (!buffer)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		index = read(fd, buffer, BUFFER_SIZE);
		flag = 1;
	}
	res = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	ft_strlcpy(res, buffer, BUFFER_SIZE + 1);
	if (is_nl(res))
	{
		trim_side(res, 0);
	}		
	while ((!is_nl(res)) && flag)
	{
		index = read(fd, buffer, BUFFER_SIZE);
		res = ft_strjoin(res, buffer);
	}
	return (get_result(res));
}
