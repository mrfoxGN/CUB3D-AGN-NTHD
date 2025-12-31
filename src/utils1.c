/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:32:01 by anguenda          #+#    #+#             */
/*   Updated: 2025/12/30 21:41:36 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <fcntl.h>

int	is_blank_line(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\v'
			&& s[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}

int	is_line_all_ones(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_line_border_valid(const char *line)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len < 2)
		return (0);
	if (line[0] != '1' || line[len - 1] != '1')
		return (0);
	return (1);
}

int	is_line_content_valid(const char *line)
{
	int	j;
	int	len;

	j = 1;
	if (!line)
		return (0);
	len = ft_strlen(line);
	while (j < len - 1)
	{
		if (line[j] != '1'
			&& line[j] != ' ' && line[j] != '0'
			&& line[j] != 'N' && line[j] != 'S'
			&& line[j] != 'E' && line[j] != 'W')
			return (0);
		j++;
	}
	return (1);
}

int	is_map_valid(char **map)
{
	int	i;
	int	lines;

	i = 0;
	if (!map || !map[0])
		return (0);
	lines = count_lignes_map(map);
	if (lines < 2)
		return (0);
	if (!is_line_all_ones(map[0]))
		return (0);
	if (!is_line_all_ones(map[lines - 1]))
		return (0);
	i = 1;
	while (i < lines - 1)
	{
		if (!is_line_border_valid(map[i]))
			return (0);
		if (!is_line_content_valid(map[i]))
			return (0);
		i++;
	}
	if (!check_enclosure(map))
		return (0);
	return (1);
}
