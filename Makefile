MAKEFLAGS += --no-print-directory

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

HEADER = fdf.h

SRC = fdf.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(LIBFT):
	@echo "📚 Compiling libft library..."
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJ)
	@echo "🔗 Linking objects and creating $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "✅ Build complete: $(NAME)"

%.o : %.c
	@echo "⚙️  Compiling ..."
	@$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "🗑️  Removing binaries..."
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
	@echo "🔄 Rebuilding everything..."

.PHONY: all clean fclean re
