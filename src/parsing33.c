/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing33.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:32:06 by anguenda          #+#    #+#             */
/*   Updated: 2025/12/30 11:32:38 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <fcntl.h>

int	process_colors(t_game *game)
{
	char	**floor;
	char	**ceiling;
	int		ok;

	floor = ft_split(game->floor_color, ',');
	ceiling = ft_split(game->ceiling_color, ',');
	ok = 1;
	if (count_elemnts(floor) != 3 || count_elemnts(ceiling) != 3)
		ok = 0;
	else
	{
		game->Floor = fill_elements(floor);
		game->Ceiling = fill_elements(ceiling);
		if (game->Floor)
			game->hexfloor = rgb_to_hex(game->Floor);
		if (game->Ceiling)
			game->hexceiling = rgb_to_hex(game->Ceiling);
	}
	free_split_arr(floor);
	free_split_arr(ceiling);
	ok = rgb_values_valid(game->Floor) && rgb_values_valid(game->Ceiling);
	return (ok);
}

int	parse_textures_and_validate(t_game *game)
{
	if (!pars_textures__argb(game))
		return (0);
	if (game->argb_parsed != 2 || game->textures_parsed != 4)
		return (0);
	return (1);
}

int	rgb_to_hex(int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (!rgb)
		return (0);
	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

char	**read_file_cub(char *file_name, t_game *game)
{
	return (read_file_cub_internal(file_name, game));
}

char	**read_file_cub_internal(char *file_name, t_game *game)
{
	char	**map;
	int		fd;

	fd = open(file_name, O_RDONLY);
	game->fd = fd;
	if (!validate_textures_or_close(game, fd))
	{
		return (NULL);
	}
	map = read_map(game);
	if (!check_map_or_close(map, file_name, fd))
	{
		return (NULL);
	}
	if (!check_colors_or_close(game, fd))
	{
		return (NULL);
	}
	close_fd_if_open(fd);
	return (map);
}
