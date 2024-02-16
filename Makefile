# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 13:02:10 by luide-so          #+#    #+#              #
#    Updated: 2024/02/16 22:38:47 by luide-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
RULE = .all
RULE_BONUS = .bonus

SRC = main parse
DEPS = cub3d.h
DEPS_PATH = mandatory/includes/

SRC_BONUS = main_bonus
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

FLAGS = -Wall -Wextra -Werror -O3
LIBFLAGS = -L $(LIBFT)_obj -lft -L $(MLX) -lmlx -lXext -lX11 -lm -lbsd

all: $(NAME)

$(NAME): $(OBJ) $(RULE)
	@$(MAKE) -s -C $(LIBFT)
	@$(MAKE) -s -C $(MLX)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I $(DEPS_PATH) $(LIBFLAGS)

	@echo "\nCub3D compiled\n"

$(OBJ_PATH)%.o: %.c $(DEPS)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@ -I $(DEPS_PATH) $(LIBFLAGS)

$(RULE):
	@touch $(RULE)
	@rm -f $(RULE_BONUS)

bonus: $(RULE_BONUS)

$(RULE_BONUS): $(OBJ_BONUS)
	@touch $(RULE_BONUS)
	@rm -f $(RULE)
	@$(MAKE) -s -C $(LIBFT)
	@$(MAKE) -s -C $(MLX)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME) -I $(DEPS_PATH_BONUS) $(LIBFLAGS)

	@echo "\nCub3D_bonus compiled\n"

$(OBJ_PATH)%_bonus.o: %_bonus.c $(DEPS_BONUS)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@ -I $(DEPS_PATH_BONUS) $(LIBFLAGS)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	@ rm -f $(RULE) $(RULE_BONUS)
	rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT) fclean
	@$(MAKE) -s -C $(MLX) clean

re: fclean all

download:
	@echo "\nDownloading mlx\n"
	@wget https://cdn.intra.42.fr/document/document/22624/minilibx-linux.tgz
	@tar -xvf minilibx-linux.tgz
	@rm -f minilibx-linux.tgz
	@echo "\nMlx downloaded\n"

.PHONY: all clean fclean re bonus
