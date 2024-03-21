/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:46:17 by barb              #+#    #+#             */
/*   Updated: 2024/01/26 20:33:53 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*remain_stat(char *stat)
{
	int		i;
	int		start;
	char	*remain;

	i = 0;
	if (stat[i] == '\0')
	{
		free(stat);
		return (NULL);
	}
	while (stat[i] != '\n' && stat[i])
		i++;
	if (stat[i] == '\n')
		i++;
	start = i;
	i = 0;
	remain = (char *)malloc((ft_strlen(stat) - start + 1) * sizeof(char));
	if (!remain)
		return (NULL);
	start--;
	while (stat[++start])
		remain[i++] = stat[start];
	remain[i] = '\0';
	free(stat);
	return (remain);
}

static char	*get_line(char	*stat)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	if (stat[i] == 0)
		return (NULL);
	while (stat[len] != '\n' && stat[len])
		len++;
	if (stat[len] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (i < len)
	{
		line[i] = stat[i];
		i++;
	}
	return (line);
}

static char	*putstat(int fd, char *stat)
{
	int		val;
	char	*buf;

	val = 1;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (!charset(stat) && val != 0)
	{
		val = read(fd, buf, BUFFER_SIZE);
		if (val < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[val] = '\0';
		stat = strjoin(stat, buf);
		if (!stat)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (stat);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat = putstat(fd, stat);
	if (!stat)
	{
		free(stat);
		return (NULL);
	}
	line = get_line(stat);
	stat = remain_stat(stat);
	if (!stat)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
