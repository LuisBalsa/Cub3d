# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 13:02:10 by luide-so          #+#    #+#              #
#    Updated: 2024/04/08 11:46:01 by luide-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
RESET = \033[0m

NAME = cub3D
RULE = .all
RULE_BONUS = .bonus

SRC = main raycasting check_hit parse lexer parse_map keys input_handler draw \
	init_mlx_and_textures
DEPS = cub3d.h
DEPS_PATH = mandatory/includes/

SRC_BONUS = parse_map_bonus lexer_bonus parse_bonus parse_sprites_bonus main_bonus \
	init_mlx_and_textures_bonus raycasting_bonus draw_bonus check_hit_bonus \
	keys_bonus input_handler_bonus mouse_handler_bonus sprites_bonus \
	perform_dda_bonus check_hit_sliding_door_bonus minimap_bonus \
	minimap_raycaster_bonus enemy_bonus draw_hud_and_more_bonus \
	check_sprite_status_bonus draw_hands_bonus draw_game_status_bonus \
	enemy_shooting_bonus draw_bullets_bonus
DEPS_BONUS = cub3d_bonus.h
DEPS_PATH_BONUS = bonus/includes/

OBJ_PATH = obj/

MLX = minilibx-linux
LIBFT = Libft

VPATH = $(shell find mandatory/ -type d)
VPATH += $(shell find bonus/ -type d)

OBJ = $(addprefix $(OBJ_PATH), $(SRC:=.o))
OBJ_BONUS = $(addprefix $(OBJ_PATH), $(SRC_BONUS:=.o))

CC = cc

FLAGS = -Wall -Wextra -Werror -O3 -g
LIBFLAGS = -L $(LIBFT)_obj -lft -L $(MLX) -lmlx -lXext -lX11 -lm -lbsd

all: $(NAME)

$(NAME): $(OBJ) $(RULE)
	@$(MAKE) -s -C $(LIBFT)
	@$(MAKE) -s makemlx 2> /dev/null || echo "$(RED)Mlx not found$(RESET)"
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I $(DEPS_PATH) $(LIBFLAGS)

	@echo "\nCub3D compiled\n"

$(OBJ_PATH)%.o: %.c $(DEPS)
	@find $(MLX) -name "mlx.h" -type f > /dev/null || $(MAKE) -s download
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@ -I $(DEPS_PATH)

$(RULE):
	@touch $(RULE)
	@rm -f $(RULE_BONUS)

bonus: $(RULE_BONUS)

$(RULE_BONUS): $(OBJ_BONUS)
	@touch $(RULE_BONUS)
	@rm -f $(RULE)
	@$(MAKE) -s -C $(LIBFT)
	@$(MAKE) -s makemlx
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME) -I $(DEPS_PATH_BONUS) $(LIBFLAGS)

	@echo "\nCub3D with bonus compiled\n"

$(OBJ_PATH)%_bonus.o: %_bonus.c $(DEPS_BONUS)
	@find $(MLX) -name "mlx.h" -type f > /dev/null || $(MAKE) -s download
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@ -I $(DEPS_PATH_BONUS)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	@ rm -f $(RULE) $(RULE_BONUS)
	rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT) fclean
	@$(MAKE) -s -C $(MLX) clean 2> /dev/null || echo "$(RED)Mlx not found$(RESET)"

re: fclean all

makemlx:
	@$(MAKE) -s -C $(MLX) || $(MAKE) -s download && $(MAKE) -s -C $(MLX)

download:
	@echo "\nDownloading mlx"
	@wget https://cdn.intra.42.fr/document/document/22624/minilibx-linux.tgz 2> /dev/null || \
	(echo "$(RED)\nMlx download failed\nPlease download it manually\n\n$(RESET)" && exit 1)
	@tar -xvf minilibx-linux.tgz > /dev/null
	@rm -f minilibx-linux.tgz
	@rm -rf minilibx-linux/.git minilibx-linux/.gitignore minilibx-linux/.github
	@echo "Mlx downloaded\n"

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/0.cub

.PHONY: all clean fclean re bonus makemlx
