#include "cube3d.h"

int main(int ac, char **argv)
{
    t_game *game;

    if (ac < 2)
        return (printf("Too few arguments"));
    game = init_game(argv);
    if (!game)
        return (1);
    mlx_loop(game->mlx.mlx_ptr);
    return (0);
}