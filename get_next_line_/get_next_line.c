/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:48:43 by anguenda          #+#    #+#             */
/*   Updated: 2025/03/19 16:03:49 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free(char *buff)
{
	if (!buff)
		return ;
	free(buff);
}

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
		return (ft_free(buff), NULL);
	i++;
	nline = ft_malloc((ft_strleen(buff) - i + 1), sizeof(char));
	if (!nline)
		return (ft_free(buff), NULL);
	while (buff[i])
	{
		nline[j] = buff[i];
		i++;
		j++;
	}
	nline[j] = '\0';
	ft_free(buff);
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
		line = ft_malloc(i + 2, sizeof(char));
	else
		line = ft_malloc(i + 1, sizeof(char));
	if (!line)
		return (ft_free(buff), NULL);
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

	readed = ft_malloc(BUFFER_SIZE + 1, sizeof(char));
	if (!readed)
		return (NULL);
	while (1)
	{
		r = read(fd, readed, BUFFER_SIZE);
		if (r < 0)
			return (ft_free(readed), ft_free(buff), NULL);
		if (!r)
			break ;
		readed[r] = 0;
		buff = ft_strjoiin(buff, readed);
		if (!buff)
			return (ft_free(readed), NULL);
	if (ft_strchr1(readed, '\n'))
			break ;
	}
	ft_free(readed);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd == -2)
		return (ft_free(buff), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buff = read_file(buff, fd);
	if (!buff)
		return (NULL);
	line = get_line(buff);
	buff = next_line(buff);
	if (!buff)
		ft_free(buff);
	return (line);
}
