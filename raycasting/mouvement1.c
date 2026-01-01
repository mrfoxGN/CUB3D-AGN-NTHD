/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:30:54 by ntahadou          #+#    #+#             */
/*   Updated: 2026/01/01 13:30:55 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

int	key_press(int key, void *param)
{
	t_game	*game;

	if (!param)
		return (1);
	game = (t_game *)param;
	if (key == XK_Escape)
	{
		close_game(game);
		exit(0);
	}
	if (key == XK_w)
		game->p.up = true;
	if (key == XK_d)
		game->p.right = true;
	if (key == XK_s)
		game->p.down = true;
	if (key == XK_a)
		game->p.left = true;
	if (key == XK_Left)
		game->p.turn_left = true;
	if (key == XK_Right)
		game->p.turn_right = true;
	return (0);
}

int	key_release(int key, void *param)
{
	t_game	*game;

	if (!param)
		return (1);
	game = (t_game *)param;
	if (key == XK_Escape)
	{
		close_game(game);
		exit(0);
	}
	if (key == XK_w)
		game->p.up = false;
	if (key == XK_d)
		game->p.right = false;
	if (key == XK_s)
		game->p.down = false;
	if (key == XK_a)
		game->p.left = false;
	if (key == XK_Left)
		game->p.turn_left = false;
	if (key == XK_Right)
		game->p.turn_right = false;
	return (0);
}

static void	fill_player_corners(float px, float py, int player_size,
		float corners[4][2])
{
	corners[0][0] = px;
	corners[0][1] = py;
	corners[1][0] = px + player_size;
	corners[1][1] = py;
	corners[2][0] = px;
	corners[2][1] = py + player_size;
	corners[3][0] = px + player_size;
	corners[3][1] = py + player_size;
}

int	is_wall(t_game *game, float px, float py)
{
	int		player_size;
	int		map_x;
	int		map_y;
	int		i;
	float	corners[4][2];

	player_size = TILE_SIZE / 5;
	fill_player_corners(px, py, player_size, corners);
	i = 0;
	while (i < 4)
	{
		map_x = (int)floorf(corners[i][0] / TILE_SIZE);
		map_y = (int)floorf(corners[i][1] / TILE_SIZE);
		if (map_x < 0 || map_y < 0 || map_y >= game->map_height
			|| map_x >= game->map_width)
			return (1);
		if (game->map[map_y] && game->map[map_y][map_x] == '1')
			return (1);
		i++;
	}
	return (0);
}
