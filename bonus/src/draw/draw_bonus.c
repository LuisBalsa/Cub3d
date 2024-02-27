/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:04:44 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/27 03:15:15 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	my_pixel_get(t_img *mlx, int x, int y)
{
	return (*(unsigned int *)(mlx->addr + \
		(y * mlx->line_len) + (x * (mlx->bpp / 8))));
}

static void	my_pixel_put(t_img *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_walls_and_background(t_game *game, t_player *pl, int x)
{
	int		y;
	int		tex_y;
	int		color;

	y = -1;
	while (++y < pl->draw.start)
		my_pixel_put(&game->screen, x, y, game->color[clg]);
	while (y < pl->draw.end)
	{
		tex_y = (int)pl->draw.pos & (TEXTURE_HEIGHT - 1);
		pl->draw.pos += pl->draw.step;
		color = my_pixel_get(&game->img[pl->img_index], pl->hit_x, tex_y);
		my_pixel_put(&game->screen, x, y, color);
		y++;
	}
	while (y < game->screen.height)
		my_pixel_put(&game->screen, x, y++, game->color[flr]);
}
