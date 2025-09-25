#include "cube3d.h"
#include "get_next_line.h"
#include <fcntl.h>


char  **read_file_cub(char *file_name, t_game *game)
{
    char **map;
    int fd = open(file_name, O_RDONLY);
    game->fd = fd;
    if (pars_textures(game))
    {
        if (pars_argb(game))
        {
           if(game->argb_parsed == 2 && game->textures_parsed == 4)
           {
                map = read_map(game);
                return (map);
           }
        }
    }
    printf("Error parsing .cub file\n");
    return (NULL);

    close(fd);
}