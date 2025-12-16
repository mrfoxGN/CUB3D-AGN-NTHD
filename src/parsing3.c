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
        values[i] = atoi(arr[i]);//we need ft_atoi here && check range 0-255
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

/* Convert an RGB array {r,g,b} to a single hex integer 0xRRGGBB */
int rgb_to_hex(int *rgb)
{
    int r = 0;
    int g = 0;
    int b = 0;

    if (!rgb)
        return 0;
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
    return (r << 16) | (g << 8) | b;
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
                    if (game->Floor)
                        game->hexfloor = rgb_to_hex(game->Floor);
                    if (game->Ceiling)
                        game->hexceiling = rgb_to_hex(game->Ceiling);

                    /* free split arrays */
                    if (floor)
                    {
                        int i = 0;
                        while (floor[i])
                        {
                            free(floor[i]);
                            i++;
                        }
                        free(floor);
                    }
                    if (ceiling)
                    {
                        int i = 0;
                        while (ceiling[i])
                        {
                            free(ceiling[i]);
                            i++;
                        }
                        free(ceiling);
                    }
                    return (map);
                }
           }
    }
    else{
    //int i = 0;
    printf("Error parsing .cub file\n");
    }
    close(fd);
    return (NULL);

}
