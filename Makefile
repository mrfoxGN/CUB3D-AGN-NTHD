NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lmlx -lXext -lX11 -lm
LIBFT_DIR = lib
LIBFT = $(LIBFT_DIR)/libft.a
SRCS =  main.c \
		raycasting/game_mock.c \
		raycasting/raycasting.c \
		raycasting/img_utils.c \
		raycasting/mouvement.c \
		raycasting/dda.c \
		src/parsing1.c src/parsing2.c src/parsing3.c\
		get_next_line_/get_next_line.c get_next_line_/get_next_line_utils.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean || true

re: fclean all

.PHONY: all clean fclean re