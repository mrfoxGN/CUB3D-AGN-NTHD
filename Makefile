
NAME = cub3d
CC = cc
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib -I$(MINILIBX_DIR) -I/usr/local/include
# Link to local minilibx first; fall back to system libs if installed
LDFLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_DIR = lib
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = main.c \
		raycasting/raycasting.c \
		raycasting/raycasting1.c \
		raycasting/raycasting2.c \
		raycasting/img_utils.c \
		raycasting/textures.c \
		raycasting/mouvement.c \
		raycasting/mouvement1.c src/utils3.c\
		raycasting/dda.c src/utils2.c\
		src/parsing11.c src/parsing22.c src/parsing33.c src/utils1.c \
		get_next_line_/get_next_line.c get_next_line_/get_next_line_utils.c \

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