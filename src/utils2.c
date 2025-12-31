/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:31:55 by anguenda          #+#    #+#             */
/*   Updated: 2025/12/30 18:08:58 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <fcntl.h>

int	is_inside_cell(char **map, int i, int j)
{
	if (i < 0 || j < 0)
		return (0);
	if (!map[i])
		return (0);
	if ((int)ft_strlen(map[i]) <= j)
		return (0);
	return (1);
}

int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

int	count_lignes_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

int	check_enclosure(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]))
			{
				if (!has_all_neighbors(map, i, j))
					return (0);
				if (!neighbors_allowed(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_and_store_player(t_game *game)
{
	int		i;
	int		j;
	int		count;
	char	c;

	if (!game || !game->map)
		return (0);
	game->player_dir = '\0';
	count = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			c = game->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (++count > 1)
					return (0);
				store_player(game, i, j, c);
			}
		}
	}
	return (count == 1);
}
