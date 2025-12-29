#include "cube3d.h"
#include <fcntl.h>

 int process_colors(t_game *game)
{
    char **floor = ft_split(game->floor_color, ',');
    char **ceiling = ft_split(game->ceiling_color, ',');
    int ok = 1;

    if (count_elemnts(floor) != 3 || count_elemnts(ceiling) != 3)// here need to check if each element is a number between 0-255
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
    ok= rgb_values_valid(game->Floor) && rgb_values_valid(game->Ceiling);
    return ok;
}


 int parse_textures_and_validate(t_game *game)
{
    if (!pars_textures__argb(game))
        return 0;
    if (game->argb_parsed != 2 || game->textures_parsed != 4)
        return 0;
    return 1;
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
    return (read_file_cub_internal(file_name, game));
}

/* forward declaration for internal helper */

/* internal helper so public read_file_cub stays under 25 lines */
 char **read_file_cub_internal(char *file_name, t_game *game)
{
    char **map; 
    int fd = open(file_name, O_RDONLY);
    game->fd = fd;
    if (!parse_textures_and_validate(game))
    {
        printf("Error parsing .cub file\n");
        close_fd_if_open(fd);
        return (NULL);
    }
    map = read_map(game);
    if (!map)
    {
        printf("Error: failed to read map from '%s'\n", file_name);
        close_fd_if_open(fd);
        return (NULL);
    }
    if (!process_colors(game))
    {
        printf("Error: Floor or Ceiling color format is incorrect\n");
        close_fd_if_open(fd);
        return (NULL);
    }
    close_fd_if_open(fd);
    return (map);
}
