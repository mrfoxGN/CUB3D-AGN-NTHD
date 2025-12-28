#include "cube3d.h"

int is_wall(t_game *game, float px, float py)
{
    int player_size = TILE_SIZE / 4;
    
    float corners[4][2] = {
        {px, py},                                   
        {px + player_size, py},                     
        {px, py + player_size},                      
        {px + player_size, py + player_size}         
    };

    for (int i = 0; i < 4; i++)
    {
        int map_x = (int)(corners[i][0] / TILE_SIZE);
        int map_y = (int)(corners[i][1] / TILE_SIZE);
        
        if (map_x < 0 || map_y < 0 || 
            map_y >= game->map_height || 
            map_x >= game->map_width)
            return (1);
            
        if (game->map[map_y] && game->map[map_y][map_x] == '1')
            return (1);
    }
    return (0);
}

int move_player(t_game *game)
{
    float cos_angle;
    float sin_angle;
    float dx;
    float dy;

    if (!game)
        return (1);

    if (game->p.turn_left)
        game->p.angle -= ROT_SPEED;
    if (game->p.turn_right)
        game->p.angle += ROT_SPEED;
    if (game->p.angle < 0)
        game->p.angle += 2 * PI_MACRO;
    if (game->p.angle >= 2 * PI_MACRO)
        game->p.angle -= 2 * PI_MACRO;

    cos_angle = cosf(game->p.angle + PI_MACRO / 2);
    sin_angle = sinf(game->p.angle + PI_MACRO / 2);

    dx = 0.0f;
    dy = 0.0f;

    if (game->p.right)
    {
        dx += cos_angle * SPEED;
        dy += sin_angle * SPEED;
    }
    if (game->p.left)
    {
        dx -= cos_angle * SPEED;
        dy -= sin_angle * SPEED;
    }
    if (game->p.up)
    {
        dx += cosf(game->p.angle) * SPEED;
        dy += sinf(game->p.angle) * SPEED;
    }
    if (game->p.down)
    {
        dx -= cosf(game->p.angle) * SPEED;
        dy -= sinf(game->p.angle) * SPEED;
    }

    if (dx != 0.0f || dy != 0.0f)
    {
        float try_x = game->p.px + dx;
        float try_y = game->p.py + dy;

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

    return (0);
}
