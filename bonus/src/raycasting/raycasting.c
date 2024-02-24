/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:21:40 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/24 18:42:04 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d_bonus.h"

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < game->screen.width)
	{
		y = -1;
		while (++y < game->screen.height / 2)
			my_pixel_put(&game->screen, x, y, game->color[clg]);
		y--;
		while (++y < game->screen.height)
			my_pixel_put(&game->screen, x, y, game->color[flr]);
	}
}

void	raycasting(t_game *game)
{
	draw_background(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
