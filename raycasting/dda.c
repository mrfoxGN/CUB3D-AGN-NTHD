#include "cube3d.h"

t_res dda(t_game *game, float ray_angle)
{
    t_player p = game->p;
    t_res result;
    
    // Calculate ray direction from angle
    float raydirx = cos(ray_angle);
    float raydiry = sin(ray_angle);

    // Calculate delta distances
    float deltax = fabs(1.0 / raydirx);
    float deltay = fabs(1.0 / raydiry);

    // Calculate current position in world coordinates
    float posx = (float)p.px / TILE_SIZE;
    float posy = (float)p.py / TILE_SIZE;

    // Calculate which box of the map we're in
    int mapx = (int)floor(posx);
    int mapy = (int)floor(posy);

    // Calculate step and initial sideDist
    float sidedistx, sidedisty;
    int stepx, stepy;

    if (raydirx < 0)
    {
        stepx = -1;
        sidedistx = (posx - mapx) * deltax;
    }
    else
    {
        stepx = 1;
        sidedistx = (mapx + 1.0 - posx) * deltax;
    }

    if (raydiry < 0)
    {
        stepy = -1;
        sidedisty = (posy - mapy) * deltay;
    }
    else
    {
        stepy = 1;
        sidedisty = (mapy + 1.0 - posy) * deltay;
    }

    // Perform DDA
    bool hit = false;
    int side; // was it a NS or a EW wall hit?

    while (!hit)
    {
        // Jump to next map square, either in x-direction, or in y-direction
        if (sidedistx < sidedisty)
        {
            sidedistx += deltax;
            mapx += stepx;
            side = 0;
        }
        else
        {
            sidedisty += deltay;
            mapy += stepy;
            side = 1;
        }

        // Check if ray has hit a wall
        if (mapx < 0 || mapy < 0 || mapx >= game->map_width || 
            mapy >= game->map_height)
        {
            hit = true; // Hit boundary
        }
        else if (game->map[mapy] && game->map[mapy][mapx] == '1')
        {
            hit = true; // Hit wall
        }
    }

    // Calculate distance
    float distance;
    if (side == 0)
        distance = (mapx - posx + (1 - stepx) / 2) / raydirx;
    else
        distance = (mapy - posy + (1 - stepy) / 2) / raydiry;

    // Fill result structure
    result.hit = hit;
    // exact hit position in tile units, then convert to pixels
    float hitx = posx + distance * raydirx;
    float hity = posy + distance * raydiry;
    result.x = (int)floorf(hitx * TILE_SIZE);
    result.y = (int)floorf(hity * TILE_SIZE);
    result.distance = distance;
    result.side = side;

    return result;
}

