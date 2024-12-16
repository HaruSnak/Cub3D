NAME = cub3D
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LIBFTDIR = includes/libft/
LIBFT_OBJ = includes/libft/includes/obj
OBJ_DIR = obj/
SRC_DIR = srcs/
MLX_DIR = minilibx-linux/
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

SRC_1 = srcs/cub3d.c
SRC_2 = srcs/errors/errors.c \
	srcs/game/settings.c \
	srcs/parsing/parsing.c \
	srcs/parsing/parsing_map.c \
	srcs/parsing/parsing_rgb.c \
	srcs/parsing/verify_direction.c \
	srcs/parsing/verify_map.c \
	srcs/raycasting/raycasting_calcul.c \
	srcs/raycasting/raycasting_draw.c \
	srcs/raycasting/raycasting_init.c \
	srcs/texturing/draw_textures.c \
	srcs/texturing/init_textures.c \
	srcs/player/init_player_controls.c \
	srcs/player/keys.c \
	srcs/player/player_movement.c \
	srcs/player/rotate.c \
	srcs/utils/function_utils.c \
	srcs/utils/parsing_utils.c \
	srcs/utils-mlx/function_mlx.c
#BONUS = srcs/utils-mlx/function_mlx.c

OBJ_1 = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC_1))
OBJ_2 = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC_2))
BONUS_OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(BONUS))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

INCLUDE = -L $(LIBFTDIR) -lft
INCLUDES = -I/usr/include -Imlx

.c.o:
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(MLX_LIB) $(OBJ_1) $(OBJ_2) $(BONUS_OBJ)
	@echo "Compiling libft..."
	@make -C $(LIBFTDIR)
	@echo "Compiling $(NAME)..."
	@$(CC) $(FLAGS) $(OBJ_1) $(OBJ_2) $(BONUS_OBJ) -o $(NAME) $(INCLUDE) $(INCLUDES) $(MLX_FLAGS)
	@echo "$(NAME) compiled successfully."

$(MLX_LIB):
	@echo "Compiling mlx..."
	@make -C $(MLX_DIR)
	@echo "mlx compiled successfully."

all: $(MLX_LIB) $(NAME)

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ_1) $(OBJ_2) $(BONUS_OBJ)
	@echo "Cleaning libft object files..."
	@make -C $(LIBFTDIR) clean
	@rm -rf $(LIBFT_OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning libft..."
	@make -C $(LIBFTDIR) fclean
	@echo "Cleaning executable..."
	@$(RM) $(NAME)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBFT_OBJ)
	@clear
	@echo "Executable and libft cleaned."

re: fclean all

.PHONY: all clean fclean re