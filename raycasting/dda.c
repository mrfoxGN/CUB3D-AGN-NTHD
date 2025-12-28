#include "cube3d.h"

static void	init_dda_vars(t_player *p, float ray_angle, t_dda *dda_vars)
{
	dda_vars->raydirx = cos(ray_angle);
	dda_vars->raydiry = sin(ray_angle);
	dda_vars->deltax = fabs(1.0 / dda_vars->raydirx);
	dda_vars->deltay = fabs(1.0 / dda_vars->raydiry);
	dda_vars->posx = (float)p->px / TILE_SIZE;
	dda_vars->posy = (float)p->py / TILE_SIZE;
	dda_vars->mapx = (int)floor(dda_vars->posx);
	dda_vars->mapy = (int)floor(dda_vars->posy);
	dda_vars->hit = false;
}

static void	init_dda(t_player *p, float ray_angle, t_dda *dda_vars)
{
	init_dda_vars(p, ray_angle, dda_vars);
	if (dda_vars->raydirx < 0)
	{
		dda_vars->stepx = -1;
		dda_vars->sidedistx = (dda_vars->posx - dda_vars->mapx)
			* dda_vars->deltax;
	}
	else
	{
		dda_vars->stepx = 1;
		dda_vars->sidedistx = (dda_vars->mapx + 1.0 - dda_vars->posx)
			* dda_vars->deltax;
	}
	if (dda_vars->raydiry < 0)
	{
		dda_vars->stepy = -1;
		dda_vars->sidedisty = (dda_vars->posy - dda_vars->mapy)
			* dda_vars->deltay;
	}
	else
	{
		dda_vars->stepy = 1;
		dda_vars->sidedisty = (dda_vars->mapy + 1.0 - dda_vars->posy)
			* dda_vars->deltay;
	}
}

static void	dda_loop(t_game *game, t_dda *dda_vars, int *side)
{
	while (1)
	{
		if (dda_vars->sidedistx < dda_vars->sidedisty)
		{
			dda_vars->sidedistx += dda_vars->deltax;
			dda_vars->mapx += dda_vars->stepx;
			*side = 0;
		}
		else
		{
			dda_vars->sidedisty += dda_vars->deltay;
			dda_vars->mapy += dda_vars->stepy;
			*side = 1;
		}
		if (dda_vars->mapx < 0 || dda_vars->mapy < 0
			|| dda_vars->mapx >= game->map_width ||
			dda_vars->mapy >= game->map_height || (game->map[dda_vars->mapy]
					&& game->map[dda_vars->mapy][dda_vars->mapx] == '1'))
		{
			dda_vars->hit = true;
			break ;
		}
	}
}

t_res	dda(t_game *game, float ray_angle)
{
	t_player	p;
	t_res		result;
	t_dda		dda_vars;
	int			side;

	p = game->p;
	init_dda(&p, ray_angle, &dda_vars);
	dda_loop(game, &dda_vars, &side);
	if (side == 0)
		dda_vars.distance = (dda_vars.mapx - dda_vars.posx + (1
					- dda_vars.stepx) / 2) / dda_vars.raydirx;
	else
		dda_vars.distance = (dda_vars.mapy - dda_vars.posy + (1
					- dda_vars.stepy) / 2) / dda_vars.raydiry;
	result.hit = dda_vars.hit;
	dda_vars.hitx = dda_vars.posx + dda_vars.distance * dda_vars.raydirx;
	dda_vars.hity = dda_vars.posy + dda_vars.distance * dda_vars.raydiry;
	result.x = (int)floorf(dda_vars.hitx * TILE_SIZE);
	result.y = (int)floorf(dda_vars.hity * TILE_SIZE);
	result.distance = dda_vars.distance;
	result.eye_dist = dda_vars.distance * cos(ray_angle - p.angle);
	result.side = side;
	return (result);
}
