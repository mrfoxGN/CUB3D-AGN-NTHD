#include "cube3d.h"



int main()
{
    t_game *game;

    game = create_mock_game();
    if (!game)
        return (1);
    game->mlx.mlx_ptr = mlx_init();
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, W_WIDTH, W_HIGHT, "Cube3D");

    minimap(game);

    mlx_loop(game->mlx.mlx_ptr);
}