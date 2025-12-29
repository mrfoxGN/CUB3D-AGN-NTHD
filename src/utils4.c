  #include "cube3d.h"
#include <fcntl.h>

void	init_parse_ctx(t_parse_ctx *ctx, t_game *game)
{
	ctx->carte = NULL;
	ctx->jeu = game;
	ctx->contenu_vu = 0;
	ctx->trou_vu = 0;
	ctx->violation_trou = 0;
	ctx->nb_lignes = -1;
}
void	free_map_all(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
