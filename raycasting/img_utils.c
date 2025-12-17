#include "cube3d.h"

void	my_mlx_pixel_put(t_img *dest, int pixel, int x, int y)
{
	t_game *game;

	game = (t_game *)dest->game;
	if (!game)
		return;
	if (x >= W_WIDTH || y >= W_HIGHT || x < 0 || y < 0)
		return ;
	*(unsigned int *)(dest->addr + (y * dest->sl) + (x * dest->bpp
				/ 8)) = pixel;
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