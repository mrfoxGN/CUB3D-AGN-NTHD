/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:32:04 by ntahadou          #+#    #+#             */
/*   Updated: 2026/01/01 14:34:59 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_square(t_draw_params params)
{
	int	i;
	int	j;

	i = params.x;
	j = params.y;
	if (!params.img || params.size <= 0)
		return ;
	while (j < params.y + params.size)
	{
		i = params.x;
		while (i < params.x + params.size)
		{
			my_mlx_pixel_put(params.img, params.color, i, j);
			i++;
		}
		j++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	if (!game)
		return ;
	i = 0;
	j = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (game->map[j][i] == '1')
				draw_square((t_draw_params){&game->img, i * TILE_SIZE, j
					* TILE_SIZE, TILE_SIZE, 0xF6F1E9});
			i++;
		}
		j++;
	}
}

int	cast_rays(t_game *game)
{
	int		i;
	t_res	res;
	float	camerax;

	if (!game)
		return (1);
	i = 0;
	while (i < W_WIDTH)
	{
		camerax = 2 * i / (float)W_WIDTH - 1;
		res = dda(game, game->p.angle + camerax * (FOV / 2));
		if (res.distance > 0.0f)
			draw_ray_seg(&(t_ray_seg){&game->img, (float)game->p.px
				+ PLAYER_SIZE / 2, (float)game->p.py + PLAYER_SIZE / 2,
				res.x, res.y, 0xE4004B});
		i += 5;
	}
	return (0);
}

void	mini_map(t_game *game)
{
	fill_window(game, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE,
		0x000000);
	draw_map(game);
	draw_square((t_draw_params){&game->img, game->p.px, game->p.py, PLAYER_SIZE,
		0xF5F5F5});
	cast_rays(game);
}
