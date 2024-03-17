/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_and_textures_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:34:06 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/17 21:47:35 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	load_enemy_textures(t_game *game, char *theme_d)
{
	game->texture[INDEX_ENEMY_IMAGE] = ft_strjoin(theme_d, ENEMY_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 1] = ft_strjoin(theme_d, ENEMY1_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 2] = ft_strjoin(theme_d, ENEMY2_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 3] = ft_strjoin(theme_d, ENEMY3_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 4] = ft_strjoin(theme_d, ENEMY4_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 5] = ft_strjoin(theme_d, ENEMY5_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 6] = ft_strjoin(theme_d, ENEMY6_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 7] = ft_strjoin(theme_d, ENEMY7_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 8] = ft_strjoin(theme_d, ENEMY8_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 9] = ft_strjoin(theme_d, ENEMY9_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 10] = ft_strjoin(theme_d, ENEMY10_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 11] = ft_strjoin(theme_d, ENEMY11_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 12] = ft_strjoin(theme_d, ENEMY12_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 13] = ft_strjoin(theme_d, ENEMY13_IMAGE);
	game->texture[INDEX_ENEMY_IMAGE + 14] = ft_strjoin(theme_d, ENEMY14_IMAGE);
}

static void	load_theme_textures(t_game *game, char *theme_d)
{
	game->texture[INDEX_DOOR_IMAGE] = ft_strjoin(theme_d, DOOR_IMAGE);
	game->texture[INDEX_DOOR_IMAGE + 1] = ft_strjoin(theme_d, DOOR_FRAME);
	game->texture[INDEX_SPRITE_IMAGE] = ft_strjoin(theme_d, CAGE_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 1] = ft_strjoin(theme_d, BARREL_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 2] = ft_strjoin(theme_d, TABLE_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 3] = ft_strjoin(theme_d, KEY_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 4] = ft_strjoin(theme_d, FIRE_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 5] = ft_strjoin(theme_d, FIRE1_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 6] = ft_strjoin(theme_d, FIRE2_IMAGE);
	game->texture[INDEX_WALL_IMAGE] = ft_strjoin(theme_d, WALL1_IMAGE);
	game->texture[INDEX_WALL_IMAGE + 1] = ft_strjoin(theme_d, WALL2_IMAGE);
	game->texture[INDEX_WALL_IMAGE + 2] = ft_strjoin(theme_d, WALL3_IMAGE);
	game->texture[INDEX_WALL_IMAGE + 3] = ft_strjoin(theme_d, WALL4_IMAGE);
	game->texture[INDEX_HIT_IMAGE] = ft_strjoin(theme_d, HIT_IMAGE);
}

static void	load_textures(t_game *game)
{
	int		i;

	load_theme_textures(game, game->theme_directory);
	load_enemy_textures(game, game->theme_directory);
	i = -1;
	while (++i < NBR_TEXTURES)
	{
		game->img[i].img = mlx_xpm_file_to_image(game->mlx, game->texture[i],
				&game->img[i].width, &game->img[i].height);
		if (!game->img[i].img)
			error_exit(game, "Failed to load texture");
		game->img[i].addr = mlx_get_data_addr(game->img[i].img,
				&game->img[i].bpp, &game->img[i].line_len,
				&game->img[i].endian);
		if (!game->img[i].addr)
			error_exit(game, "Failed to get texture address");
	}
}

void	init_mlx_and_textures(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(game, "Failed to initialize mlx");
	load_textures(game);
	game->screen.width = (int)SCREEN_WIDTH;
	game->screen.height = (int)SCREEN_HEIGHT;
	game->screen.img = mlx_new_image(game->mlx, game->screen.width,
			game->screen.height);
	if (!game->screen.img)
		error_exit(game, "Failed to create new image");
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	if (!game->screen.addr)
		error_exit(game, "Failed to get image address");
	game->win = mlx_new_window(game->mlx, game->screen.width,
			game->screen.height, "Cub3D Bonus");
	if (!game->win)
		error_exit(game, "Failed to create new window");
}
