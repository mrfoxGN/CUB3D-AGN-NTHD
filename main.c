#include "cube3d.h"

void init_game(t_game *game)
{
    game->p.angle = -PI_MACRO / 2;
    game->p.dirx = 0; 
    game->p.diry = -1;
    
    game->p.planex = 0.66;
    game->p.planey = 0;

    game->p.up = false;
    game->p.left = false;
    game->p.down = false;
    game->p.right = false;
    game->p.turn_left = false;
    game->p.turn_right = false;

    game->img.game = (void *)game;
}


int main(int ac, char **av)
{
    t_game *game;

    if (ac != 2)
        return(0);

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    game->map = read_file_cub(av[1], game);
    if (!game->map)
        return(1);
    init_game(game);
    raycasting(game);
    mlx_loop(game->mlx.mlx_ptr);
}