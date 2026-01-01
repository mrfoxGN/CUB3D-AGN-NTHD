#include "cube3d.h"


void free_mlx(t_game *game)
{
	int i;

	if (!game)
		return;
	if (game->img.ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.ptr);
	for (i = 0; i < 4; i++)
	{
		if (game->tex[i].ptr)
			mlx_destroy_image(game->mlx.mlx_ptr, game->tex[i].ptr);
	}
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
		mlx_destroy_display(game->mlx.mlx_ptr);
	free(game->mlx.mlx_ptr);
}

void	*gc_malloc(size_t size, int mode)
{
	static t_list	*head_list;
	t_list			*new_node;
	void			*content;

	new_node = NULL;
	content = NULL;
	if (mode == 1)
	{
		content = malloc(size);
		if (!content)
		{
			ft_putstr_fd("malloc Failed: ", STDERR_FILENO);
			gc_malloc(0, 0);
			exit (EXIT_FAILURE);
		}
		new_node = ft_lstnew(content);
		ft_lstadd_back(&head_list, new_node);
	}
	else if (mode == 0)
	{
		ft_lstclear(&head_list, free);
		head_list = NULL;
	}
	return (content);
}

int close_game(t_game *game)
{
    free_mlx(game);
    
    // if (game->map)
    // {
    //     int i = 0;
    //     while (game->map[i])
    //         free(game->map[i++]);
    //     free(game->map);
    // }

    gc_malloc(0, 1); 

    free(game);

    printf("Game closed cleanly\n");
    exit(0);
    return (0);
}