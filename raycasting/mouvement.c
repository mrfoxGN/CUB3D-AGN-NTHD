#include "cube3d.h"

static void	normalize_angle(float *angle)
{
	while (*angle < 0.0f)
		*angle += 2 * PI_MACRO;
	while (*angle >= 2 * PI_MACRO)
		*angle -= 2 * PI_MACRO;
}

static void	handle_rotation(t_game *game)
{
	if (game->p.turn_left)
		game->p.angle -= ROT_SPEED;
	if (game->p.turn_right)
		game->p.angle += ROT_SPEED;
	normalize_angle(&game->p.angle);
}

static void	compute_move_vector(t_game *game, float *dx, float *dy)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cosf(game->p.angle + PI_MACRO / 2);
	sin_angle = sinf(game->p.angle + PI_MACRO / 2);
	if (game->p.right)
	{
		*dx += cos_angle * SPEED;
		*dy += sin_angle * SPEED;
	}
	if (game->p.left)
	{
		*dx -= cos_angle * SPEED;
		*dy -= sin_angle * SPEED;
	}
	if (game->p.up)
	{
		*dx += cosf(game->p.angle) * SPEED;
		*dy += sinf(game->p.angle) * SPEED;
	}
	if (game->p.down)
	{
		*dx -= cosf(game->p.angle) * SPEED;
		*dy -= sinf(game->p.angle) * SPEED;
	}
}

static void	apply_movement(t_game *game, float dx, float dy)
{
	float	try_x;
	float	try_y;

	if (dx == 0.0f && dy == 0.0f)
		return ;
	try_x = game->p.px + dx;
	try_y = game->p.py + dy;
	if (!is_wall(game, try_x, try_y))
	{
		game->p.px = try_x;
		game->p.py = try_y;
	}
	else if (!is_wall(game, try_x, game->p.py))
	{
		game->p.px = try_x;
	}
	else if (!is_wall(game, game->p.px, try_y))
	{
		game->p.py = try_y;
	}
}

int	move_player(t_game *game)
{
	float	dx;
	float	dy;

	if (!game)
		return (1);
	dx = 0.0f;
	dy = 0.0f;
	handle_rotation(game);
	compute_move_vector(game, &dx, &dy);
	apply_movement(game, dx, dy);
	return (0);
}
