#include "cube3d.h"

void	set_player_dir(t_game *game)
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

static int	load_texture(t_game *game, t_img *img, char *path)
{
    int	w;
    int	h;

    if (!path)
        return (1);
    img->ptr = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, &w, &h);
    if (!img->ptr)
        return (printf("Failed to load texture: %s\n", path), 1);
    img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->sl, &img->end);
    img->w = w;
    img->h = h;
    img->game = game;
    return (0);
}

int	load_textures(t_game *game)
{
    if (!game)
        return (1);
    if (load_texture(game, &game->tex[0], game->no_texture) != 0)
        return (1);
    if (load_texture(game, &game->tex[1], game->so_texture) != 0)
        return (1);
    if (load_texture(game, &game->tex[2], game->we_texture) != 0)
        return (1);
    if (load_texture(game, &game->tex[3], game->ea_texture) != 0)
        return (1);
    return (0);
}

void	init_game(t_game *game)
{
	if (!game)
		return ;
	game->mlx.mlx_ptr = mlx_init();
	if (load_textures(game))
		close_game(game);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, W_WIDTH, W_HIGHT,
			"Cube3D");
	game->img.ptr = mlx_new_image(game->mlx.mlx_ptr, W_WIDTH, W_HIGHT);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.sl, &game->img.end);
	set_player_dir(game);
	game->p.up = false;
	game->p.left = false;
	game->p.down = false;
	game->p.right = false;
	game->p.turn_left = false;
	game->p.turn_right = false;
	game->img.game = (void *)game;
}

int	main(int ac, char **av)
{
	t_game *game;

	if (ac != 2)
		return (0);
	if (!check_cub_extension(av[1]))
    {
        ft_putstr_fd("Error: File must have .cub extension\n", STDERR_FILENO);
        return (1);
    }
	game = malloc(sizeof(t_game));
	ft_bzero(game, sizeof(t_game));
	if (!game)
		return (1);
	game->map = read_file_cub(av[1], game);
	if (!game->map)
	{
		close_game(game);
		return (1);
	}
	init_game(game);
	raycasting(game);
	mlx_loop(game->mlx.mlx_ptr);
	return (0);
}
