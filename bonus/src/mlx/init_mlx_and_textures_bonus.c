/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_and_textures_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:34:06 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/02 22:49:32 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	load_textures(t_game *game)
{
	int		i;

	game->texture[INDEX_DOOR_IMAGE] = ft_strdup(DOOR_IMAGE);
	game->texture[INDEX_DOOR_IMAGE + 1] = ft_strdup(DOOR_FRAME);
	game->texture[INDEX_SPRITE_IMAGE] = ft_strdup(ENEMY_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 1] = ft_strdup(CAGE_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 2] = ft_strdup(BARREL_IMAGE);
	game->texture[INDEX_SPRITE_IMAGE + 3] = ft_strdup(TABLE_IMAGE);
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
