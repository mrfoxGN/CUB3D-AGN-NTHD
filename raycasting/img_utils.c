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