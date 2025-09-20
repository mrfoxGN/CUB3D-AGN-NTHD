#include "cube3d.h"
#include <fcntl.h>
char *get_next_line(int fd)
{
    char *buf = malloc(BUFFER_SIZE + 1);
    char *line = NULL;
    int bytes_read, i = 0;
    if (!buf)
        return NULL;
    bytes_read = read(fd, buf, BUFFER_SIZE);
    if (bytes_read <= 0)
    {
        free(buf);
        return NULL;
    }
    buf[bytes_read] = '\0';
    while (buf[i] && buf[i] != '\n')
        i++;
    line = malloc(i + 2);
    if (!line)
    {
        free(buf);
        return NULL;
    }
    for (int j = 0; j <= i; j++)
        line[j] = buf[j];
    line[i + (buf[i] == '\n' ? 1 : 0)] = '\0';
    free(buf);
    return line;
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
char **read_map(char *file_name,t_game *game)
{
    char *line[2];
    char **map = NULL;
    int readed_line = -1;
    game->fd = open(file_name, O_RDONLY);
    if (game->fd < 0)
        return (NULL);
    while (1)
    {
        line[0] = get_next_line(game->fd);
        if (!line[0])
            break;
        line[1] = ft_strtrim(line[0], "\n");
        free(line[0]);
        if(line[1] && line[1][0])
        {
            char **tmp = expand_ligne_map(map, line[1]);
            if (!tmp)
            {
                free(line[1]);
                break;
            }
            map = tmp;
            readed_line++;
        }
        if ((int)ft_strlen(line[1]) > (int)game->map_width)
        {
            game->map_width = ft_strlen(line[1]);
        }
        else
        {
            free(line[1]);
        }
    }
    game->map_height = readed_line;
    close(game->fd);
    return (map);
}