#include "cube3d.h"

void set_player_dir(t_game *game)
{
    if (game->player_dir == 'N')
        game->p.angle = -PI_MACRO / 2;
    else if (game->player_dir == 'S')
        game->p.angle = PI_MACRO / 2;
    else if (game->player_dir == 'E')
        game->p.angle = 0;
    else
        game->p.angle = PI_MACRO;

    game->p.dirx = cos(game->p.angle); 
    game->p.diry = sin(game->p.angle);    
}

void init_game(t_game *game)
{
    if (!game)
        return;
    
    set_player_dir(game);
    
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