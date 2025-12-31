/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:31:37 by anguenda          #+#    #+#             */
/*   Updated: 2025/12/30 11:32:58 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_colors_or_close(t_game *game, int fd)
{
	if (process_colors(game))
		return (1);
	printf("Error: Floor or Ceiling color format is incorrect\n");
	close_fd_if_open(fd);
	return (0);
}

int	check_map_or_close(char **map, char *file_name, int fd)
{
	if (map)
		return (1);
	printf("Error: failed to read map from '%s'\n", file_name);
	close_fd_if_open(fd);
	return (0);
}

int	validate_textures_or_close(t_game *game, int fd)
{
	if (!parse_textures_and_validate(game))
	{
		printf("Error parsing .cub file\n");
		close_fd_if_open(fd);
		return (0);
	}
	return (1);
}
