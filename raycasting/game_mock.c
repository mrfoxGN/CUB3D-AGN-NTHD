#include "cube3d.h"

t_game *create_mock_game(void)
{
    t_game *game = malloc(sizeof(t_game));
    if (!game)
        return NULL;

    // Initialize MLX structure
    game->mlx.mlx_ptr = NULL;  // Will be set by mlx_init()
    game->mlx.win_ptr = NULL;  // Will be set by mlx_new_window()
    
    // File descriptor
    game->fd = -1;  // Invalid fd initially
    
    
    // Map dimensions
    game->map_width = 10;
    game->map_height = 13;
    
    // Mock map (simple rectangular map)
    game->map = malloc(sizeof(char*) * (game->map_height + 1));
    game->map[0] = strdup("1111111111");
    game->map[1] = strdup("1000000001");
    game->map[2] = strdup("1000N00001");  // N = North-facing player
    game->map[3] = strdup("1000001001");
    game->map[4] = strdup("1010000001");
    game->map[5] = strdup("1000010001");
    game->map[6] = strdup("1010000101");
    game->map[7] = strdup("1010000101");
    game->map[8] = strdup("1010000101");
    game->map[9] = strdup("1010010101");
    game->map[10] = strdup("1010100101");
    game->map[11] = strdup("1010000101");
    game->map[12] = strdup("1010000101");
    game->map[13] = strdup("1111111111");
    game->map[14] = NULL;  // Null-terminated


    // Player direction
    game->player_dir = 'N';  // North
    
    // Texture paths
    // game->no_texture = strdup("./assets/textures/north_wall.xpm");
    // game->so_texture = strdup("./assets/textures/south_wall.xpm");
    // game->we_texture = strdup("./assets/textures/west_wall.xpm");
    // game->ea_texture = strdup("./assets/textures/east_wall.xpm");
    
    // Color strings (RGB format)
    game->floor_color = strdup("220,100,0");    // Brown floor
    game->ceiling_color = strdup("135,206,235"); // Sky blue ceiling
    
    // Parsing flags
    game->textures_parsed = 1;  // Textures successfully parsed
    game->argb_parsed = 1;      // Colors successfully parsed
    
    // Color arrays (RGB values)
    game->Floor = malloc(sizeof(int) * 3);
    game->Floor[0] = 220;  // R
    game->Floor[1] = 100;  // G
    game->Floor[2] = 0;    // B
    
    game->Ceiling = malloc(sizeof(int) * 3);
    game->Ceiling[0] = 135;  // R
    game->Ceiling[1] = 206;  // G
    game->Ceiling[2] = 235;  // B
    
    game->p.px = game->map_width * TILE_SIZE / 2;
    game->p.py = game->map_height * TILE_SIZE / 2;

    game->p.up = false;
    game->p.left = false;
    game->p.down = false;
    game->p.right = false;
    game->p.turn_left = false;
    game->p.turn_right = false;
    
    // Initialize direction vectors for North-facing player
    game->p.angle = -PI_MACRO / 2; // -90 degrees (North)
    game->p.dirx = 0;  // North direction
    game->p.diry = -1;
    
    // Camera plane (perpendicular to direction, pointing right)
    game->p.planex = 0.66;  // FOV control
    game->p.planey = 0;

    // game struct
    game->img.game = (void *)game;
    
    return game;
}
