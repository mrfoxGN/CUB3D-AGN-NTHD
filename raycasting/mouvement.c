#include "cube3d.h"
#include <math.h>

int key_press(int key, void *param)
{
    t_player *p;

    if (!param)
        return (1);
    p = (t_player *)param;
    if (key == XK_Escape)
        exit(0);
    if (key == XK_w)
        p->up = true;
    if (key == XK_d)
        p->right = true;
    if (key == XK_s)
        p->down = true;
    if (key == XK_a)
        p->left = true;
    if (key == XK_Left)
        p->turn_left = true;
    if (key == XK_Right)
        p->turn_right = true;
    return (0);
}

int key_release(int key, void *param)
{
    t_player *p;

    if (!param)
        return (1);
    p = (t_player *)param;
    if (key == XK_Escape)
        exit(0);
    if (key == XK_w)
        p->up = false;
    if (key == XK_d)
        p->right = false;
    if (key == XK_s)
        p->down = false;
    if (key == XK_a)
        p->left = false;
    if (key == XK_Left)
        p->turn_left = false;
    if (key == XK_Right)
        p->turn_right = false;
    return (0);
}

int is_wall(t_game *game, int px, int py)
{
    int player_size = TILE_SIZE / 4;
    
    int corners[4][2] = {
        {px, py},                                    // Top-left
        {px + player_size, py},                      // Top-right
        {px, py + player_size},                      // Bottom-left
        {px + player_size, py + player_size}         // Bottom-right
    };
    
    for (int i = 0; i < 4; i++)
    {
        int map_x = corners[i][0] / TILE_SIZE;
        int map_y = corners[i][1] / TILE_SIZE;
        
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

    cos_angle = cosf(game->p.angle + PI_MACRO/2);
    sin_angle = sinf(game->p.angle + PI_MACRO/2);

    if (game->p.right && !is_wall(game, game->p.px + SPEED, game->p.py))
    {
        game->p.px += cos_angle * SPEED;
        game->p.py += sin_angle * SPEED;
    }

    if (game->p.left && !is_wall(game, game->p.px - SPEED, game->p.py))
    {
        game->p.px -= cos_angle * SPEED;
        game->p.py -= sin_angle * SPEED;
    }

    if (game->p.up && !is_wall(game, game->p.px, game->p.py - SPEED))
    {
        game->p.px += cosf(game->p.angle) * SPEED;
        game->p.py += sinf(game->p.angle) * SPEED;
    }

    if (game->p.down && !is_wall(game, game->p.px, game->p.py + SPEED))
    {
        game->p.px -= cosf(game->p.angle) * SPEED;
        game->p.py -= sinf(game->p.angle) * SPEED;
    }

    return (0);
}
