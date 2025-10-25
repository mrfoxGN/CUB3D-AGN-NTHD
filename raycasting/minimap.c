#include "cube3d.h"

void draw_square(t_img *img, int x, int y, int size, int color)
{
    int i;
    int j;

    if (!img || size <= 0)
        return;
    for (j = y; j < y + size; j++)
    {
        for (i = x; i < x + size; i++)
            my_mlx_pixel_put(img, color, i, j);
    }
}

void fill_window(t_game *game, int w, int h ,int color)
{
    int i;
    int j;
    
    if (!game)
        return;
    i = 0;
    j = 0;
    while (i < h)
    {
        j = 0;
        while (j < w)
        {
            my_mlx_pixel_put(&game->img, color, j,i);
            j++;
        }
        i++;
    }
}

void draw_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(game->map[j])
    {
        i = 0;
        while (game->map[j][i])
        {
            if (game->map[j][i] == '1')
                draw_square(&game->img, i * TILE_SIZE, j* TILE_SIZE,TILE_SIZE,0x00ffff);
            i++;
        }
        j++;
    }
}

void draw_ray_seg(t_img *img, float sx, float sy, float ex, float ey, int color)
{
    int steps;
    float dx = ex - sx;
    float dy = ey - sy;
    float abs_dx = dx < 0 ? -dx : dx;
    float abs_dy = dy < 0 ? -dy : dy;
    float x_inc, y_inc;
    float x, y;
    int i;

    if (!img)
        return;

    steps = (int)(abs_dx > abs_dy ? abs_dx : abs_dy);
    if (steps == 0)
    {
        my_mlx_pixel_put(img, color, (int)sx, (int)sy);
        return;
    }

    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;
    x = sx;
    y = sy;
    for (i = 0; i <= steps; ++i)
    {
        my_mlx_pixel_put(img, color, (int)x, (int)y);
        x += x_inc;
        y += y_inc;
    }
}

int cast_rays(t_game *game)
{
    const int rays_number = W_WIDTH;
    int i;
    t_res res;
    float camerax;
    const float fov = PI_MACRO / 3;
    float ray_angle;

    if (!game)
        return (1);

    for (i = 0; i < rays_number; ++i)
    {
        camerax = 2 * i / (float)rays_number - 1;
        ray_angle = game->p.angle + camerax * (fov / 2);
        res = dda(game, ray_angle);
        
        if (res.distance > 0.0f)
            draw_ray_seg(&game->img, (float)game->p.px + PLAYER_SIZE /2, (float)game->p.py + PLAYER_SIZE /2, res.x, res.y, 0xFFFF00);
    }
    return (0);
}

void draw_vertical_line(t_img *img, int x, int drawstart, int drawend, int color)
{
    int i;

    i = drawstart;
    while (i < drawend)
    {
        my_mlx_pixel_put(img, color, x, i);
        i++;
    }
}

int view_3d(t_game *game)
{
    const int rays_number = W_WIDTH;
    int i;
    t_res res;
    float camerax;
    const float fov = PI_MACRO / 3;
    float ray_angle;

    if (!game)
        return (1);

    for (i = 0; i < rays_number; ++i)
    {
        camerax = 2 * i / (float)rays_number - 1;
        ray_angle = game->p.angle + camerax * (fov / 2);
        res = dda(game, ray_angle);
    
        int lineheight = W_HIGHT / res.eye_dist;
        int draw_start = W_HIGHT/2 - lineheight/2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = W_HIGHT/2 + lineheight/2;
        if (draw_end > W_HIGHT)
            draw_end = W_HIGHT - 1;

        if (res.distance > 0.0f)
        {
            draw_vertical_line(&game->img,i,draw_start, draw_end ,0xFFFF00);
            draw_vertical_line(&game->img,i,0, draw_start ,0xFF00FF00);
            draw_vertical_line(&game->img,i,draw_end, W_HIGHT ,0x00FFFF);
        }
    }

    return (0);
}

void mini_map(t_game *game)
{
    fill_window(game, game->map_width * TILE_SIZE , game->map_height * TILE_SIZE ,0xFF00FF);
    draw_map(game);
    draw_square(&game->img, game->p.px , game->p.py, PLAYER_SIZE, 0xffffff);
    cast_rays(game);
}

int draw_loop(t_game *game)
{
    move_player(game);
    fill_window(game, W_WIDTH, W_HIGHT ,0x000000);
   
    view_3d(game);
    mini_map(game);

    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->img.ptr, 0, 0);
    return(0);
}

int minimap(t_game *game)
{
    if (!game)
        return (1);
    
    game->img.ptr = mlx_new_image(game->mlx.mlx_ptr, W_WIDTH, W_HIGHT);
    game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,&game->img.sl, &game->img.end);

    mlx_hook(game->mlx.win_ptr, KeyPress,KeyPressMask,key_press, &game->p);
    mlx_hook(game->mlx.win_ptr, KeyRelease,KeyReleaseMask,key_release, &game->p);

    mlx_loop_hook(game->mlx.mlx_ptr, draw_loop, game);
    return (0);
}