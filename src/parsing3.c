#include "cube3d.h"
#include <fcntl.h>
int *fill_elements(char **arr)
{
    int *values;
    int i;

    values = malloc(3 * sizeof(int));
    if (!values)
        return (NULL);
    i = 0;
    while (i < 3)
    {
        values[i] = 0;
        i++;
    }
    i = 0;
    while (arr && arr[i] && i < 3)
    {
        values[i] = atoi(arr[i]);
        i++;
    }
    return (values);
}
int count_elemnts(char **arr)
{
    int count = 0;
    if (!arr)
        return 0;
    while (arr[count])
        count++;
    return count;
}

char  **read_file_cub(char *file_name, t_game *game)
{
    char **map;
    char **floor;
    char **ceiling;
    int fd = open(file_name, O_RDONLY);
    game->fd = fd;
    if (pars_textures__argb(game))
    {
           if(game->argb_parsed == 2 && game->textures_parsed == 4)
           {
                map = read_map(game);
                if(map)
                {
                    floor = ft_split(game->floor_color, ',');
                    ceiling = ft_split(game->ceiling_color, ',');
                    if(count_elemnts(floor) != 3 || count_elemnts(ceiling) != 3)
                    {
                        printf("Error: Floor or Ceiling color format is incorrect\n");
                        map = NULL;
                    }
                    game->Floor = fill_elements(floor);
                    game->Ceiling = fill_elements(ceiling);
                    return (map);
                }
           }
    } 
    else
    {
        printf("Error parsing .cub file\n");
    }
    return (NULL);

    close(fd);
}
