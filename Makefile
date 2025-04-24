MAKEFLAGS += --no-print-directory

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address

RM = rm -f

LIBFT = libft
GNL = gnl

HEADER = -I$(LIBFT) -I$(GNL) -I.

SRC = $(GNL)/get_next_line.c $(GNL)/get_next_line_utils.c \
		fdf.c validation.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	@echo "🔗 Linking objects and creating $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT) -lft
	@echo "✅ Build complete: $(NAME)"

$(LIBFT)/libft.a:
	@echo "📚 Compiling libft library..."
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) bonus -C $(LIBFT)

%.o: %.c
	@echo "⚙️  Compiling $<..."
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@echo "🗑️  Removing binaries..."
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

re: fclean all
	@echo "🔄 Rebuilding everything..."

.PHONY: all clean fclean re
