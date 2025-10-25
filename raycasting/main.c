#include "cube3d.h"

int main()
{
    t_game *game;

    game = create_mock_game();
    if (!game)
        return (1);

    raycasting(game);

    mlx_loop(game->mlx.mlx_ptr);
}