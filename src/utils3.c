  #include "cube3d.h"
#include <fcntl.h>
void close_fd_if_open(int fd)
{
    if (fd >= 0)
        close(fd);
}
void free_split_arr(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
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
 int rgb_values_valid(int *rgb)
{
    int i;
    if (!rgb)
        return 0;
    i = 0;
    while (i < 3)
    {
        if (rgb[i] < 0 || rgb[i] > 255)
            return 0;
        i++;
    }
    return 1;
}
 /*main.c \
		raycasting/raycasting.c \
		raycasting/raycasting1.c \
		raycasting/raycasting2.c \
		raycasting/img_utils.c \
		raycasting/textures.c \
		raycasting/mouvement.c \
		raycasting/mouvement1.c src/utils3.c\
		raycasting/dda.c src/utils2.c\
		src/parsing11.c src/parsing22.c src/parsing33.c src/utils1.c \
		get_next_line_/get_next_line.c get_next_line_/get_next_line_utils.c \*/
