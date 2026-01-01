/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:31:33 by ntahadou          #+#    #+#             */
/*   Updated: 2026/01/01 13:31:49 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	calculate_wall_color(float distance, int side)
{
	int		wall_color;
	float	shade_factor;

	wall_color = 0x80D8C3;
	shade_factor = 1.0f - (distance / 40.0f);
	if (shade_factor < 0.2f)
		shade_factor = 0.2f;
	if (side == 1)
		shade_factor *= 0.7f;
	return (darken_color(wall_color, shade_factor));
}

int	view_3d(t_game *game)
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
			draw_column(game, res, i, game->p.angle + camerax * (FOV / 2));
		i++;
	}
	return (0);
}

int	draw_loop(t_game *game)
{
	move_player(game);
	view_3d(game);
	mini_map(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->img.ptr,
		0, 0);
	return (0);
}

int	raycasting(t_game *game)
{
	if (!game)
		return (1);
	mlx_hook(game->mlx.win_ptr, 17, 0, close_game, game);
	mlx_hook(game->mlx.win_ptr, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx.win_ptr, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_loop_hook(game->mlx.mlx_ptr, draw_loop, game);
	return (0);
}
