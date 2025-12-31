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
#include "../get_next_line_/get_next_line.h"

#define PI_MACRO 3.14159265358979323846

#define W_HIGHT 1000
#define W_WIDTH 1400
#define TILE_SIZE 16
#define SPEED 0.5
#define ROT_SPEED 0.03
#define PLAYER_SIZE 3
#define FOV PI_MACRO / 3

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

typedef struct s_pixel
{
    int x;
    int y;
    int color;
}t_pixel;

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

typedef struct s_res
{
    bool hit;
    int x;
    int y;
    float distance;
    float eye_dist;
    int side;
}t_res;

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
    int hexfloor;
    int hexceiling;
    t_img img;
    t_player p;
    t_img tex[4];
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

typedef struct s_dda
{
    float raydirx;
    float raydiry;
    float deltax;
    float deltay;
    float posx;
    float posy;
    int mapx;
    int mapy;
    float sidedistx;
    float sidedisty;
    int stepx;
    int stepy;
    bool hit;
    float distance;
}               t_dda;

// Functions
// **********************

// init
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
 void	init_parse_ctx(t_parse_ctx *ctx, t_game *game);
/*static int check_enclosure(char **map);
static int is_allowed(char c);
static int is_inside_cell(char **map, int i, int j);*/

/////////////////////////////////////////

int raycasting(t_game *game);

// Movement functions
int key_press(int key, void *param);
int key_release(int key, void *param);
int move_player(t_game *game);

// DDA raycasting function
t_res dda(t_game *game, float camerax);

// Utils
void    draw_column(t_game *game, t_res res, int i, float ray_angle);
void	my_mlx_pixel_put(t_img *dest, int pixel, int x, int y);
int darken_color(int color, float factor);
void draw_ray_seg(t_img *img, float sx, float sy, float ex, float ey, int color);
void fill_window(t_game *game, int w, int h ,int color);
void draw_vertical_line(t_img *img, int x, int drawstart, int drawend, int color);
int is_wall(t_game *game, float px, float py);
int is_blank_line(const char *s);
int is_line_all_ones(const char *line);
int is_line_border_valid(const char *line);
int is_line_content_valid(const char *line);
int check_and_store_player(t_game *game);
 int is_inside_cell(char **map, int i, int j);
 int is_allowed(char c);
int check_enclosure(char **map);
int is_map_valid(char **map);
int count_lignes_map(char **map);
char **expand_ligne_map(char **old_map, char *new_line);
void free_map_all(char **map);
int append_trimmed_line(t_parse_ctx *ctx, char *line_trim);
int process_raw_line(t_parse_ctx *ctx, char *raw);
void read_lines_into_map(int fd, t_parse_ctx *ctx);
char **read_map(t_game *game);

int pars_textures__argb(t_game *game);
int pars_argb(char *line,t_game *game);
int pars_textures(char *line,t_game *game);
int	is_only_spaces(const char *s);


char **read_file_cub_internal(char *file_name, t_game *game);
int rgb_to_hex(int *rgb);
int parse_textures_and_validate(t_game *game);
 void close_fd_if_open(int fd);
 int process_colors(t_game *game);
 void free_split_arr(char **arr);
 int count_elemnts(char **arr);
 int *fill_elements(char **arr);
  int rgb_values_valid(int *rgb);
  int	validate_textures_or_close(t_game *game, int fd);
  int	check_map_or_close(char **map, char *file_name, int fd);
  int	check_colors_or_close(t_game *game, int fd);
  void	store_player(t_game *game, int i, int j, char c);
  int	neighbors_allowed(char **map, int i, int j);
  int	has_all_neighbors(char **map, int i, int j);
   int	is_walkable(char c);

void mini_map(t_game *game);

#endif