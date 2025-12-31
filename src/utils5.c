/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:31:43 by anguenda          #+#    #+#             */
/*   Updated: 2025/12/30 11:33:00 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <fcntl.h>

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	has_all_neighbors(char **map, int i, int j)
{
	if (!is_inside_cell(map, i - 1, j) || !is_inside_cell(map, i + 1, j))
		return (0);
	if (!is_inside_cell(map, i, j - 1) || !is_inside_cell(map, i, j + 1))
		return (0);
	return (1);
}

int	neighbors_allowed(char **map, int i, int j)
{
	if (!is_allowed(map[i - 1][j]) || !is_allowed(map[i + 1][j]))
		return (0);
	if (!is_allowed(map[i][j - 1]) || !is_allowed(map[i][j + 1]))
		return (0);
	return (1);
}

void	store_player(t_game *game, int i, int j, char c)
{
	game->player_dir = c;
	game->p.px = j * (float)TILE_SIZE + (TILE_SIZE / 2.0f);
	game->p.py = i * (float)TILE_SIZE + (TILE_SIZE / 2.0f);
}
