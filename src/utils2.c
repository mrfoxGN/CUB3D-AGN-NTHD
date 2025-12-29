 #include "cube3d.h"
#include <fcntl.h>
 int is_inside_cell(char **map, int i, int j)
{
    if (i < 0 || j < 0)
        return 0;
    if (!map[i])
        return 0;
    if ((int)ft_strlen(map[i]) <= j)
        return 0;
    return 1;
}
 int is_allowed(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
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

 int check_enclosure(char **map)
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
int check_and_store_player(t_game *game)
{
    int i, j, count = 0;
    char c;

    if (!game || !game->map)
        return 0;
    game->player_dir = '\0';
    for (i = 0; game->map[i]; ++i)
        for (j = 0; game->map[i][j]; ++j)
            if ((c = game->map[i][j]) == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (++count > 1)
                    return 0;
                game->player_dir = c;
                game->p.px = j * (float)TILE_SIZE + (TILE_SIZE / 2.0f);
                game->p.py = i * (float)TILE_SIZE + (TILE_SIZE / 2.0f);
            }
    return count == 1;
}
