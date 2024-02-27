/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_and_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:34:06 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/24 20:23:17 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	load_textures(t_game *game)
{
	int		i;

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
