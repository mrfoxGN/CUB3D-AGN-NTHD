/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 14:52:21 by ntahadou          #+#    #+#             */
/*   Updated: 2026/01/01 15:21:01 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	get_tex_num(t_res res, float ray_angle)
{
	if (res.side == 0)
	{
		if (cos(ray_angle) > 0)
			return (2);
		return (3);
	}
	else
	{
		if (sin(ray_angle) > 0)
			return (1);
		return (0);
	}
}

static int	get_tex_x(t_game *game, t_res res, float ray_angle, int tex_num)
{
	float	wall_x;
	int		tex_x;

	if (res.side == 0)
		wall_x = (float)game->p.py / TILE_SIZE + res.distance * sin(ray_angle);
	else
		wall_x = (float)game->p.px / TILE_SIZE + res.distance * cos(ray_angle);
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)game->tex[tex_num].w);
	if ((res.side == 0 && cos(ray_angle) > 0) || (res.side == 1
			&& sin(ray_angle) < 0))
		tex_x = game->tex[tex_num].w - tex_x - 1;
	return (tex_x);
}

static void	render_textured_wall(t_render_wall *params)
{
	float	step;
	float	tex_pos;
	int		vars[3];
	int		color;
	int		*tex_addr;

	step = 1.0 * params->game->tex[params->tex_num].h / params->lineheight;
	tex_pos = (params->draw_start - W_HIGHT / 2 + params->lineheight / 2)
		* step;
	tex_addr = (int *)params->game->tex[params->tex_num].addr;
	vars[0] = params->draw_start;
	vars[1] = (int)tex_pos & (params->game->tex[params->tex_num].h - 1);
	vars[2] = 0;
	while (vars[0] < params->draw_end)
	{
		vars[1] = (int)tex_pos & (params->game->tex[params->tex_num].h - 1);
		tex_pos += step;
		color = tex_addr[params->game->tex[params->tex_num].h * vars[1]
			+ params->tex_x];
		if (params->res.side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&params->game->img, color, params->x, vars[0]);
		vars[0]++;
	}
}

void	draw_column(t_game *game, t_res res, int i, float ray_angle)
{
	int			lineheight;
	int			draw[2];
	int			tex_num;
	int			tex_x;
	t_draw_line	line;

	lineheight = (int)(W_HIGHT / res.eye_dist);
	draw[0] = (W_HIGHT / 2) - (lineheight / 2);
	draw[1] = (W_HIGHT / 2) + (lineheight / 2);
	tex_num = get_tex_num(res, ray_angle);
	tex_x = get_tex_x(game, res, ray_angle, tex_num);
	if (draw[0] < 0)
		draw[0] = 0;
	if (draw[1] >= W_HIGHT)
		draw[1] = W_HIGHT;
	line = (t_draw_line){&game->img, i, 0, draw[0], game->hexceiling};
	draw_vertical_line(&line);
	render_textured_wall(&(t_render_wall){game, res, i, tex_num, tex_x,
		lineheight, draw[0], draw[1]});
	line = (t_draw_line){&game->img, i, draw[1], W_HIGHT, game->hexfloor};
	draw_vertical_line(&line);
}
