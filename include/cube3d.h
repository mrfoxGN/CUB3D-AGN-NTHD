#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#ifdef USE_MINILIBX
# include <mlx.h>
#endif
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
    char player_dir;
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    char *floor_color;
    char *ceiling_color;
     int textures_parsed;
    int argb_parsed;
    
} t_game;
typedef struct s_parse_ctx
{
    char    **carte;
    t_game  *jeu;
    int     contenu_vu;
    int     trou_vu;
    int     violation_trou;
    int     nb_lignes;
    int num_of_players;
}   t_parse_ctx;

// Functions
// **********************

// init
t_game *init_game(char **argv);
char	*get_next_line(int fd);
char **read_map(t_game *game);
char **expand_ligne_map(char **old_map,char *new_line);
int count_lignes_map(char **map);
int is_line_border_valid(const char *line);
int is_line_content_valid(const char *line);
int is_map_valid(char **map);
int is_line_all_ones(const char *line);
int check_and_store_player(t_game *game);
int pars_textures(t_game *gamed);
int pars_argb(t_game *game);
char  **read_file_cub(char *file_name, t_game *game);
int	is_only_spaces(const char *s);
/*static int check_enclosure(char **map);
static int is_allowed(char c);
static int is_inside_cell(char **map, int i, int j);*/
#endif