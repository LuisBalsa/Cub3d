/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:04:44 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/12 14:52:36 by luide-so         ###   ########.fr       */
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

	if (color == (int)0x980088)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_minimap_tile(t_game *game, t_vi2d	pos_index, int color)
{
	t_vi2d	pos;
	int		i;
	int		j;

	if (color == -1)
		return ;
	pos = (t_vi2d){(pos_index.x + MINIMAP_OFFSET) * MINIMAP_TILE_S,
		(pos_index.y + MINIMAP_OFFSET) * MINIMAP_TILE_S};
	i = -1;
	while (++i < MINIMAP_TILE_S)
	{
		j = -1;
		while (++j < MINIMAP_TILE_S)
			my_pixel_put(&game->screen, pos.x + j, pos.y + i, color);
	}
}

void	draw_sprites(t_game *game, t_sprite sprite, int pitch)
{
	int		x;
	int		y;

	x = sprite.draw_start.x - 1;
	while (++x < sprite.draw_end.x)
	{
		sprite.tex.x = (int)(256 * (x - (sprite.screen_x - sprite.width / 2))
				* TEXTURE_WIDTH / sprite.width) / 256;
		if (sprite.transform.y > 0 && sprite.transform.y < game->wall_dist[x])
		{
			y = sprite.draw_start.y - 1;
			while (++y < sprite.draw_end.y)
			{
				sprite.tex.y = ((((y - pitch) * 256 - SCREEN_HEIGHT * 128 + \
					sprite.height * 128) * TEXTURE_HEIGHT) / \
						sprite.height) / 256;
				if (sprite.img_index != -1)
					my_pixel_put(&game->screen, x, y, \
							my_pixel_get(&game->img[sprite.img_index
							+ sprite.anim * game->anim_index], \
							sprite.tex.x, sprite.tex.y));
			}
		}
	}
}

void	draw_walls_and_background(t_game *game, t_player *pl, int x)
{
	int		y;
	int		tex_y;
	int		color;

	y = -1;
	while (++y < pl->draw.start)
		my_pixel_put(&game->screen, x, y, game->color[clg]);
	while (y < pl->draw.end && pl->hit_x < TEXTURE_WIDTH)
	{
		tex_y = (int)pl->draw.pos & (TEXTURE_HEIGHT - 1);
		pl->draw.pos += pl->draw.step;
		color = my_pixel_get(&game->img[pl->img_index], pl->hit_x, tex_y);
		my_pixel_put(&game->screen, x, y, color);
		y++;
	}
	y = pl->draw.end - 1;
	while (y < game->screen.height)
		my_pixel_put(&game->screen, x, y++, game->color[flr]);
}
