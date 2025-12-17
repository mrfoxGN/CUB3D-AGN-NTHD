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

void draw_ray_seg(t_img *img, float sx, float sy, float ex, float ey, int color)
{
    int steps;
    float dx;
    float dy;
    float x_inc;
    float y_inc;
    float x;
    float y;
    int i;

    if (!img)
        return;
    dx = ex - sx;
    dy = ey - sy;
    i = 0;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;
    x = sx;
    y = sy;
    while ( i <= steps)
    {
        my_mlx_pixel_put(img, color, (int)x, (int)y);
        x += x_inc;
        y += y_inc;
        i++;
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

int darken_color(int color, float factor)
{
    if (factor > 1.0f) factor = 1.0f;
    if (factor < 0.0f) factor = 0.0f;
    
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    
    r = (int)(r * factor);
    g = (int)(g * factor);
    b = (int)(b * factor);
    
    return (r << 16) | (g << 8) | b;
}

int view_3d(t_game *game)
{
    int i;
    t_res res;
    float camerax;
    float ray_angle;
    int lineheight;
    int draw_start;
    int draw_end;
    if (!game)
        return (1);
    i = 0;
    while ( i < W_WIDTH)
    {
        camerax = 2 * i / (float)W_WIDTH - 1;
        ray_angle = game->p.angle + camerax * (FOV / 2);
        res = dda(game, ray_angle);
    
        lineheight = W_HIGHT / res.eye_dist;
        draw_start = W_HIGHT/2 - lineheight/2;
        if (draw_start < 0)
            draw_start = 0;
        draw_end = W_HIGHT/2 + lineheight/2;
        if (draw_end > W_HIGHT)
            draw_end = W_HIGHT - 1;
        if (res.distance > 0.0f)
        {
            int wall_color = 0x80D8C3;
            
            float shade_factor = 1.0f - (res.distance / 40.0f); // Adjust 20.0f for fog distance
            if (shade_factor < 0.2f) shade_factor = 0.2f; // Minimum brightness
            
            if (res.side == 1) // N/S walls are darker
                shade_factor *= 0.7f;
            
            wall_color = darken_color(wall_color, shade_factor);
            
            draw_vertical_line(&game->img, i, 0, draw_start, game->hexceiling);
            draw_vertical_line(&game->img, i, draw_start, draw_end, wall_color);
            draw_vertical_line(&game->img, i, draw_end, W_HIGHT, game->hexfloor);
        }
        i++;
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

int draw_loop(t_game *game)
{
    move_player(game);
    fill_window(game, W_WIDTH, W_HIGHT ,0x000000);
   
    view_3d(game);
    mini_map(game);

    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->img.ptr, 0, 0);
    return(0);
}

int raycasting(t_game *game)
{
    if (!game)
        return (1);
    game->mlx.mlx_ptr = mlx_init();
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, W_WIDTH, W_HIGHT, "Cube3D");
    game->img.ptr = mlx_new_image(game->mlx.mlx_ptr, W_WIDTH, W_HIGHT);
    game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,&game->img.sl, &game->img.end);

    mlx_hook(game->mlx.win_ptr, KeyPress,KeyPressMask,key_press, &game->p);
    mlx_hook(game->mlx.win_ptr, KeyRelease,KeyReleaseMask,key_release, &game->p);
    mlx_loop_hook(game->mlx.mlx_ptr, draw_loop, game);
    return (0);
}