MAKEFLAGS += --no-print-directory

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SOURCE  = src
LIBRARY = library

EVENTS = $(SOURCE)/events
MAP = $(SOURCE)/map
RENDER = $(SOURCE)/render
UTILS = $(SOURCE)/utils
INCLUDES = $(SOURCE)/includes

LIBFT = $(LIBRARY)/libft
GNL = $(LIBRARY)/gnl
MLX = $(LIBRARY)/mlx

HEADER = -I$(LIBFT) -I$(GNL) -I$(MLX) -I$(SOURCE) -I$(INCLUDES)

SRC = $(GNL)/get_next_line.c $(GNL)/get_next_line_utils.c \
		$(EVENTS)/input_handler.c $(EVENTS)/window_utils.c \
		$(MAP)/map_loader.c $(MAP)/map_parser.c \
		$(RENDER)/point_utils.c $(RENDER)/bresenham.c $(RENDER)/draw_utils.c \
		$(RENDER)/projection.c $(RENDER)/transformation.c \
		$(UTILS)/memory_utils.c $(UTILS)/validation_utils.c \
		$(SOURCE)/main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(MLX)/libmlx.a $(OBJ) $()
	@echo "🔗 Linking objects and creating $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm -lz
	@echo "✅ Build complete: $(NAME)"

$(LIBFT)/libft.a:
	@echo "📚 Compiling libft library..."
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) bonus -C $(LIBFT)

$(MLX)/libmlx.a:
	@echo "🎨 Compiling mlx library..."
	@$(MAKE) -C $(MLX) > /dev/null 2>&1

%.o: %.c
	@echo "⚙️  Compiling $<..."
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT)
	@$(MAKE) clean -C $(MLX)

fclean: clean
	@echo "🗑️  Removing binaries..."
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
