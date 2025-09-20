#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include "../lib/libft.h"

#define W_HIGHT 800
#define W_WIDTH 800
#define BUFFER_SIZE 42

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;
} t_mlx;

typedef struct s_game
{
    t_mlx mlx;
    int fd;
    char **map;
    int map_width;
    int map_height;
    
} t_game;

// Functions
// **********************

// init
t_game *init_game(char **argv);
char	*get_next_line(int fd);

#endif