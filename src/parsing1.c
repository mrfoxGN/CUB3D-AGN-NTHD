#include "cube3d.h"
#include <fcntl.h>
// #include "get_next_line.h"

static int is_blank_line(const char *s)
{
    int i = 0;
    if (!s || s[0] == '\0')
        return 1;
    while (s[i])
    {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\v' && s[i] != '\f')
            return 0;
        i++;
    }
    return 1;
}
int is_line_all_ones(const char *line)
    {
        int i = 0;
        if (!line)
            return 0;
        while (line[i])
        {
            if (line[i] != '1')
                return 0;
            i++;
        }
        return 1;
    }
int is_line_border_valid(const char *line)
    {
        int len;
        if (!line)
            return 0;
        len = ft_strlen(line);
        if (len < 2)
            return 0;
        if (line[0] != '1' || line[len-1] != '1')
            return 0;
        return 1;
    }

    int is_line_content_valid(const char *line)
    {
        int j = 1;
        int len;
        if (!line)
            return 0;
        len = ft_strlen(line);
        while (j < len-1)
        {
            if (line[j] != '1' && line[j] != '0'
                && line[j] != 'N' && line[j] != 'S'
                && line[j] != 'E' && line[j] != 'W')
                return 0;
            j++;
        }
        return 1;
    }

int check_and_store_player(t_game *game)
{
    int i = 0;
    int j;
    int count = 0;
    char c;
    if (!game || !game->map)
        return 0;
    game->player_dir = '\0';
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            c = game->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                count++;
                game->player_dir = c;
                if (count > 1)
                    return 0;
            }
            j++;
        }
        i++;
    }
    return count == 1;
}

static int is_inside_cell(char **map, int i, int j)
{
    if (i < 0 || j < 0)
        return 0;
    if (!map[i])
        return 0;
    if ((int)ft_strlen(map[i]) <= j)
        return 0;
    return 1;
}

static int is_allowed(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int check_enclosure(char **map)
{
    int i = 0;
    int j;
    char c;
    while (map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            c = map[i][j];
            if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (!is_inside_cell(map, i-1, j) || !is_inside_cell(map, i+1, j) ||
                    !is_inside_cell(map, i, j-1) || !is_inside_cell(map, i, j+1))
                    return 0;
                if (!is_allowed(map[i-1][j]) || !is_allowed(map[i+1][j]) ||
                    !is_allowed(map[i][j-1]) || !is_allowed(map[i][j+1]))
                    return 0;
            }
            j++;
        }
        i++;
    }
    return 1;
}

 int is_map_valid(char **map)
{
        int i = 0;
        int lines;
        if (!map || !map[0])
            return 0;
        lines = count_lignes_map(map);
        if (lines < 2)
            return 0;
        // First line all '1'
        if (!is_line_all_ones(map[0]))
            return 0;
        // Last line all '1'
        if (!is_line_all_ones(map[lines-1]))
            return 0;
        i = 1;
        while (i < lines-1)
        {
            if (!is_line_border_valid(map[i]))
                return 0;
            if (!is_line_content_valid(map[i]))
                return 0;
            i++;
        }
        if (!check_enclosure(map))
            return 0;
        return 1;
    }


int count_lignes_map(char **map)
{
    int i = 0;
    if (!map)
        return 0;
    while (map[i])
        i++;
    return i;
}
char **expand_ligne_map(char **old_map, char *new_line)
{
    int old_size = count_lignes_map(old_map);
    char **new_map = malloc(sizeof(char *) * (old_size + 2));
    int i = 0;
    if (!new_map)
        return old_map;
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
    return new_map;
}
static void free_map_all(char **map)
{
    int i = 0;
    while (map && map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

static int append_trimmed_line(t_parse_ctx *ctx, char *line_trim)
{
    char **tmp = expand_ligne_map(ctx->carte, line_trim);
    if (!tmp)
        return 0;
    ctx->carte = tmp;
    if ((int)ft_strlen(line_trim) > (int)ctx->jeu->map_width)
        ctx->jeu->map_width = ft_strlen(line_trim);
    return 1;
}

static int process_raw_line(t_parse_ctx *ctx, char *raw)
{
    char *trim = ft_strtrim(raw, "\n");
    free(raw);
    if (is_blank_line(trim))
    {
        if (ctx->contenu_vu && !ctx->trou_vu)
            ctx->trou_vu = 1;
        free(trim);
        return 1;
    }
    if (trim && trim[0])
    {
        if (ctx->trou_vu)
            ctx->violation_trou = 1;
        if (!append_trimmed_line(ctx, trim))
        {
            free(trim);
            return 0;
        }
        ctx->contenu_vu = 1;
        ctx->nb_lignes++;
    }
    free(trim);
    return 1;
}

static void read_lines_into_map(int fd, t_parse_ctx *ctx)
{
    char *raw;
    while (1)
    {
        raw = get_next_line(fd);
        if (!raw)
            break;
        if (!process_raw_line(ctx, raw))
            break;
    }
}

char **read_map(t_game *game)
{
    t_parse_ctx ctx;
    ctx.carte = NULL;
    ctx.jeu = game;
    ctx.contenu_vu = 0;
    ctx.trou_vu = 0;
    ctx.violation_trou = 0;
    ctx.nb_lignes = -1;
    read_lines_into_map(game->fd, &ctx);
    if (ctx.violation_trou || !is_map_valid(ctx.carte))
    {
        free_map_all(ctx.carte);
        close(game->fd);
        return NULL;
    }
    game->map = ctx.carte;
    if (!check_and_store_player(game))
    {
        free_map_all(ctx.carte);
        game->map = NULL;
        close(game->fd);
        return NULL;
    }
    game->map_height = ctx.nb_lignes + 1;
    close(game->fd);
    return ctx.carte;
}
