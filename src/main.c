#include "../include/cube3d.h"

int main(int ac, char **argv)
{
    int i = 0;
    t_game *game;

    if (ac < 2)
        return (printf("Too few arguments"));
    game = init_game(argv);
    if (!game)
        return (1);
    game->map = read_map(argv[1], game);
    if (!game->map)
        return (1);
    while( i < game->map_height)
    {
        printf("map[%d] = %s", i, game->map[i]);
        i++;
    }
    mlx_loop(game->mlx.mlx_ptr);
    return (0);
}