/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:48:43 by anguenda          #+#    #+#             */
/*   Updated: 2026/01/01 12:09:24 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"
#include "get_next_line.h"

static char	*next_line(char *buff)
{
	char	*nline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
		return (NULL);
	i++;
	nline = gc_malloc((ft_strleen(buff) - i + 1), 1);
	if (!nline)
		return (NULL);
	while (buff[i])
	{
		nline[j] = buff[i];
		i++;
		j++;
	}
	nline[j] = '\0';
	return (nline);
}

static char	*get_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		line = gc_malloc(i + 2, sizeof(char));
	else
		line = gc_malloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*read_file(char *buff, int fd)
{
	char	*readed;
	ssize_t	r;

	readed = gc_malloc(BUFFER_SIZE + 1, sizeof(char));
	if (!readed)
		return (NULL);
	while (1)
	{
		r = read(fd, readed, BUFFER_SIZE);
		if (r < 0)
			return (NULL);
		if (!r)
			break ;
		readed[r] = 0;
		buff = ft_strjoin(buff, readed);
		if (!buff)
			return (NULL);
		if (ft_strchr1(readed, '\n'))
			break ;
	}
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd == -2)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buff = read_file(buff, fd);
	if (!buff)
		return (NULL);
	line = get_line(buff);
	buff = next_line(buff);
	return (line);
}
