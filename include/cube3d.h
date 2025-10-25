#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>
#include <X11/keysym.h>
# include <X11/X.h>
#include <math.h>
#include "../lib/libft.h"
#define PI_MACRO 3.14159265358979323846

#define W_HIGHT 800
#define W_WIDTH 1200
#define TILE_SIZE 32
#define BUFFER_SIZE 42
#define SPEED 1
#define ROT_SPEED 0.01
#define PLAYER_SIZE 10

typedef struct s_player
{
    float px;
    float py;

    int dirx;
    int diry;

    float planex;
    float planey;

    float angle;

    bool up; 
    bool down; 
    bool right; 
    bool left; 

    bool turn_left;
    bool turn_right;
    
}t_player;

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;
} t_mlx;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				h;
	int				w;
	int				bpp;
	int				end;
	int				sl;
	int				p_x;
	int				p_y;
	int				direction;
    void            *game;
}					t_img;

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
    int *Floor;
    int *Ceiling;
    t_img img;
    t_player p;
    
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
char  **read_file_cub(char *file_name, t_game *game);
int	is_only_spaces(const char *s);
int pars_textures__argb(t_game *game);
int pars_argb(char *line,t_game *game);
int pars_textures(char *line,t_game *game);
/*static int check_enclosure(char **map);
static int is_allowed(char c);
static int is_inside_cell(char **map, int i, int j);*/

/////////////////////////////////////////

t_game *create_mock_game(void);
int minimap(t_game *game);
void	my_mlx_pixel_put(t_img *dest, int pixel, int x, int y);

int key_press(int key, void *param);
int key_release(int key, void *param);
int move_player(t_game *game);

// DDA raycasting function
typedef struct s_res
{
    bool hit;
    int x;
    int y;
    float distance;
    int side;
}t_res;

t_res dda(t_game *game, float camerax);

// Raycasting functions

#endif