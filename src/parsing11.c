/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing11.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:32:18 by anguenda          #+#    #+#             */
/*   Updated: 2026/01/01 13:01:07 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	**expand_ligne_map(char **old_map, char *new_line)
{
	char	**new_map;
	int		i;
	int		old_size;

	old_size = count_lignes_map(old_map);
	new_map = gc_malloc(sizeof(char *) * (old_size + 2), 1);
	i = 0;
	if (!new_map)
		return (old_map);
	if (old_map)
	{
		while (old_map[i])
		{
			new_map[i] = old_map[i];
			i++;
		}
	}
	new_map[i] = ft_strdup(new_line);
	new_map[i + 1] = NULL;
	return (new_map);
}

int	append_trimmed_line(t_parse_ctx *ctx, char *line_trim)
{
	char	**tmp;

	tmp = NULL;
	tmp = expand_ligne_map(ctx->carte, line_trim);
	if (!tmp)
		return (0);
	ctx->carte = tmp;
	if ((int)ft_strlen(line_trim) > (int)ctx->jeu->map_width)
		ctx->jeu->map_width = ft_strlen(line_trim);
	return (1);
}

int	process_raw_line(t_parse_ctx *ctx, char *raw)
{
	char	*trim;

	trim = ft_strtrim(raw, "\n");
	if (is_blank_line(trim))
	{
		if (ctx->contenu_vu && !ctx->trou_vu)
			ctx->trou_vu = 1;
		return (1);
	}
	if (trim && trim[0])
	{
		if (ctx->trou_vu)
			ctx->violation_trou = 1;
		if (!append_trimmed_line(ctx, trim))
		{
			return (0);
		}
		ctx->contenu_vu = 1;
		ctx->nb_lignes++;
	}
	return (1);
}

void	read_lines_into_map(int fd, t_parse_ctx *ctx)
{
	char	*raw;

	while (1)
	{
		raw = get_next_line(fd);
		if (!raw)
			break ;
		if (!process_raw_line(ctx, raw))
			break ;
	}
}

char	**read_map(t_game *game)
{
	t_parse_ctx	ctx;

	game->map_width = 0;
	game->map_height = 0;
	init_parse_ctx(&ctx, game);
	read_lines_into_map(game->fd, &ctx);
	if (ctx.violation_trou || !is_map_valid(ctx.carte))
	{
		close(game->fd);
		return (NULL);
	}
	game->map = ctx.carte;
	if (!check_and_store_player(game))
	{
		game->map = NULL;
		close(game->fd);
		return (NULL);
	}
	game->map_height = ctx.nb_lignes + 1;
	close(game->fd);
	return (ctx.carte);
}
