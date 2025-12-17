#include "cube3d.h"

void draw_square(t_img *img, int x, int y, int size, int color)
{
    int i;
    int j;

    i = x;
    j = y;
    if (!img || size <= 0)
        return;
    while (j < y + size )
    {
        i = x;
        while (i < x + size)
        {
            my_mlx_pixel_put(img, color, i, j);
            i++;
        }
        j++;
    }
}

void draw_map(t_game *game)
{
    int i;
    int j;

    if (!game)
        return;
    i = 0;
    j = 0;
    while(game->map[j])
    {
        i = 0;
        while (game->map[j][i])
        {
            if (game->map[j][i] == '1')
                draw_square(&game->img, i * TILE_SIZE, j* TILE_SIZE,TILE_SIZE,0xF6F1E9);
            i++;
        }
        j++;
    }
}

int cast_rays(t_game *game)
{
    int i;
    t_res res;
    float camerax;
    float ray_angle;

    if (!game)
        return (1);

    for (i = 0; i < W_WIDTH; ++i)
    {
        camerax = 2 * i / (float)W_WIDTH - 1;
        ray_angle = game->p.angle + camerax * (FOV / 2);
        res = dda(game, ray_angle);
        if (res.distance > 0.0f)
            draw_ray_seg(&game->img, (float)game->p.px + PLAYER_SIZE /2, (float)game->p.py + PLAYER_SIZE /2, res.x, res.y, 0xE4004B);
    }
    return (0);
}

void mini_map(t_game *game)
{
    fill_window(game, game->map_width * TILE_SIZE , game->map_height * TILE_SIZE ,0x000000);
    draw_map(game);
    draw_square(&game->img, game->p.px , game->p.py, PLAYER_SIZE, 0xF5F5F5);
    cast_rays(game);
}
