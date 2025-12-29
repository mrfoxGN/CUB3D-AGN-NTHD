#include "cube3d.h"
static int get_tex_num(t_res res, float ray_angle)
{
    if (res.side == 0) // Vertical wall (East/West)
    {
        if (cos(ray_angle) > 0)
            return (2); // WEST texture (facing player looking east)
        return (3);     // EAST texture
    }
    else // Horizontal wall (North/South)
    {
        if (sin(ray_angle) > 0)
            return (1); // SOUTH texture (facing player looking south)
        return (0);     // NORTH texture
    }
}

static int get_tex_x(t_game *game, t_res res, float ray_angle, int tex_num)
{
    float wall_x;
    int tex_x;

    // Calculate exact hit point on wall
    if (res.side == 0)
        wall_x = (float)game->p.py / TILE_SIZE + res.distance * sin(ray_angle);
    else
        wall_x = (float)game->p.px / TILE_SIZE + res.distance * cos(ray_angle);
    
    wall_x -= floor(wall_x); // Fractional part
    
    // Map to texture width
    tex_x = (int)(wall_x * (float)game->tex[tex_num].w);

    // Flip texture to prevent mirroring based on side
    if ((res.side == 0 && cos(ray_angle) > 0) || (res.side == 1 && sin(ray_angle) < 0))
        tex_x = game->tex[tex_num].w - tex_x - 1;
        
    return (tex_x);
}

static void render_textured_wall(t_game *game, t_res res, int x, int tex_num, int tex_x, int lineheight, int draw_start, int draw_end)
{
    float step;
    float tex_pos;
    int y;
    int color;
    int *tex_addr;

    step = 1.0 * game->tex[tex_num].h / lineheight;
    // Starting texture coordinate, account for clipping if wall > screen height
    tex_pos = (draw_start - W_HIGHT / 2 + lineheight / 2) * step;
    
    tex_addr = (int *)game->tex[tex_num].addr;
    y = draw_start;
    while (y < draw_end)
    {
        // Mask with (h - 1) only if height is power of 2, otherwise use %
        int tex_y = (int)tex_pos & (game->tex[tex_num].h - 1);
        tex_pos += step;
        
        color = tex_addr[game->tex[tex_num].h * tex_y + tex_x];
        
        // Simple shade: darken horizontal (Side 1) walls
        if (res.side == 1)
            color = (color >> 1) & 8355711;
            
        my_mlx_pixel_put(&game->img, color, x, y);
        y++;
    }
}

void    draw_column(t_game *game, t_res res, int i, float ray_angle)
{
    int lineheight;
    int draw_start;
    int draw_end;
    int tex_num;
    int tex_x;

    // Calculate dimensions
    lineheight = (int)(W_HIGHT / res.eye_dist);
    draw_start = (W_HIGHT / 2) - (lineheight / 2);
    draw_end = (W_HIGHT / 2) + (lineheight / 2);

    // Pick texture and horizontal slice
    tex_num = get_tex_num(res, ray_angle);
    tex_x = get_tex_x(game, res, ray_angle, tex_num);

    // Render Ceiling
    draw_vertical_line(&game->img, i, 0, (draw_start < 0 ? 0 : draw_start), game->hexceiling);

    // Render Wall
    render_textured_wall(game, res, i, tex_num, tex_x, lineheight, 
        (draw_start < 0 ? 0 : draw_start), (draw_end >= W_HIGHT ? W_HIGHT : draw_end));

    // Render Floor
    draw_vertical_line(&game->img, i, (draw_end >= W_HIGHT ? W_HIGHT : draw_end), W_HIGHT, game->hexfloor);
}