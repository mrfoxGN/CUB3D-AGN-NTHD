#include "cube3d.h"

int calculate_wall_color(float distance, int side)
{
    int wall_color = 0x80D8C3;
    float shade_factor = 1.0f - (distance / 40.0f);
    if (shade_factor < 0.2f)
        shade_factor = 0.2f;
    if (side == 1)
        shade_factor *= 0.7f;
    return (darken_color(wall_color, shade_factor));
}

void draw_column(t_game *game, t_res res, int i)
{
    int lineheight = W_HIGHT / res.eye_dist;
    int draw_start = (W_HIGHT / 2) - (lineheight / 2);
    int draw_end = (W_HIGHT / 2) + (lineheight / 2);
    
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end > W_HIGHT)
        draw_end = W_HIGHT - 1;
    
    draw_vertical_line(&game->img, i, 0, draw_start, game->hexceiling);
    draw_vertical_line(&game->img, i, draw_start, draw_end, 
    calculate_wall_color(res.distance, res.side));
    draw_vertical_line(&game->img, i, draw_end, W_HIGHT, game->hexfloor);
}

int view_3d(t_game *game)
{
    int i;
    t_res res;
    float camerax;
    
    if (!game)
        return (1);
    i = 0;
    while (i < W_WIDTH)
    {
        camerax = 2 * i / (float)W_WIDTH - 1;
        res = dda(game, game->p.angle + camerax * (FOV / 2));
        if (res.distance > 0.0f)
            draw_column(game, res, i);
        i++;
    }
    return (0);
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
