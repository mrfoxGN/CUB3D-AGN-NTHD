NAME    := cub3d
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCLUDES:= -Iinclude -Ilibft

LIBS    := -lmlx -lm -lX11 -lXext

# List source filenames relative to src/
SRCS    := main.c init_game.c
BIN_DIR := bin
OBJS    := $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))

# Libft
LIBFT_DIR := lib
LIBFT_A   := $(LIBFT_DIR)/libft.a

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_A) -o $(NAME) $(LIBS)

# Build objects in bin/ from sources in src/
$(BIN_DIR)/%.o: src/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(BIN_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re