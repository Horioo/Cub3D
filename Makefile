NAME = cub3d

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a
INC = inc/

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I #-fsanitize=address
MLX_FLAGS = minilibx-linux/libmlx.a -lXext -lX11
GNL_FILES = gnl/get_next_line.c gnl/get_next_line_utils.c
RM = rm -f

FILES = cub3d.c $(GNL_FILES)


SRCS = $(FILES)

OBJ = $(SRCS:.o=.c)

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(PRINTF):
	@make -C ./ft_printf

$(MLX):
	@$(MAKE) -C ./minilibx-linux

$(NAME):		$(OBJ) $(LIBFT) $(PRINTF) $(MLX)
				$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
				@echo "$(NAME) created"
clean:

	@make -C ./libft fclean --no-print-directory

fclean:			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)
					@$(RM) $(MLX)
					@echo "$(NAME) deleted"

re:				fclean all

.PHONY:				start all clean fclean re