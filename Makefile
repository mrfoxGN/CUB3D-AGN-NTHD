NAME = cub3d
CC = cc
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib -I$(MINILIBX_DIR) -I/usr/local/include
# Link to local minilibx first; fall back to system libs if installed
LDFLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_DIR = lib
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = raycasting/main.c \
		raycasting/game_mock.c \
		raycasting/raycasting.c \
		raycasting/img_utils.c \
		raycasting/mouvement.c \
		raycasting/dda.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean || true
	$(MAKE) -C $(MINILIBX_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean || true
	$(MAKE) -C $(MINILIBX_DIR) fclean || true

re: fclean all

.PHONY: all clean fclean re