#include "cube3d.h"

int init_player(t_game *game);
int parse_args(char *filename);

t_game *init_game(char **argv)
{
    t_game *game;

    if (parse_args(argv[1]) == -1)
        return (NULL);
    (void)argv;
    game = calloc(1, sizeof(t_game));
    if (!game)
        return (NULL);
    game->mlx.mlx_ptr = mlx_init();
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, W_WIDTH, W_HIGHT, "Cube3D");
    return(game);
}

int init_player(t_game *game)
{
    (void)game;
    return(0);
}

int parse_args(char *filename)
{
    char *pt_position;

    if (!filename)
        return (-1);
    pt_position = ft_strchr(filename, '.');
    if (!pt_position || ft_strcmp(pt_position, ".cub") != 0)
        return(printf("Error : invalide map\n"), -1);
    return (0);
}