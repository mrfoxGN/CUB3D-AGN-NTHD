#include "cube3d.h"
#include <fcntl.h>

int	is_only_spaces(const char *s)
{
    int i = 0;
    if (!s)
        return 1;
    while (s[i])
    {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\v' && s[i] != '\f' && s[i] != '\n')
            return 0;
        i++;
    }
    return 1;
}
int pars_textures(char *line,t_game *game)
{
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
    {
        game->no_texture = strdup((line + 3));
        game->textures_parsed++;
    }
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
    {
        game->so_texture = strdup((line + 3));
        game->textures_parsed++;
    }
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
    {
        game->we_texture = strdup((line + 3));
        game->textures_parsed++;
    }
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
    {
        game->ea_texture = strdup((line + 3));
        game->textures_parsed++;
    }
    else if (line[0] != '\0' && !is_only_spaces(line))
    {
        return 0;
    }
    return 1;
}
int pars_argb(char *line,t_game *game)
{
    if (line[0] == 'F' && line[1] == ' ')
    {
        game->floor_color = strdup(line + 2);
        game->argb_parsed++;
    }
    else if (line[0] == 'C' && line[1] == ' ')
    {
        game->ceiling_color = strdup(line + 2);
        game->argb_parsed++;
    }
    else if (line[0] != '\0' && !is_only_spaces(line))
    {
        return 0;
    }
    return 1;
}

int pars_textures__argb(t_game *game)
{
    game->textures_parsed=0;
    game->argb_parsed=0;
    char *line;
    char *line1;
    int i = 0;  
    if (!game)
        return 0;
    while (game->textures_parsed < 4 || game->argb_parsed < 2)
    {
        line = get_next_line(game->fd);
        if (!line)
            return 0;
        line1=ft_strtrim(line, "\n");
        free(line);
        line=line1;
        if(!pars_textures(line,game) && !pars_argb(line,game))
        {
                return (0);
        }
        free(line);
        i++;
    }
    return 1;
}
