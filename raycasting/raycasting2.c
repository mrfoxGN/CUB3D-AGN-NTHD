#include "cube3d.h"

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
