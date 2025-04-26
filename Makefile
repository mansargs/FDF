MAKEFLAGS += --no-print-directory

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address

RM = rm -f

LIBFT = libft
GNL = gnl
MLX = mlx

HEADER = -I$(LIBFT) -I$(GNL) -I. -I$(MLX)

SRC = $(GNL)/get_next_line.c $(GNL)/get_next_line_utils.c \
		fdf.c validation.c matrix.c cleaning_functions.c \
		render_window.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(MLX)/libmlx.a $(OBJ)
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
	@echo "⚙️  Compiling ..."
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
	@$(MAKE) clean -C $(MLX)

re: fclean all
	@echo "🔄 Rebuilding everything..."

.PHONY: all clean fclean re
