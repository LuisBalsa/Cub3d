/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bullets_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:17 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/20 11:56:40 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	draw_bullet(t_game *game, t_img *img, int bullet_index, bool active)
{
	t_vi2d	scr;
	t_vi2d	texture;
	t_vi2d	initial_pos;
	t_vi2d	bullet_s;
	int		color;

	bullet_s = (t_vi2d){img->width * BULLET_SCALE, img->height * BULLET_SCALE};
	initial_pos = (t_vi2d){game->screen.width - BULLET_OFFSET - bullet_s.x
		* BULLET_QTY, game->screen.height - BULLET_OFFSET - bullet_s.y};
	scr.y = -1;
	while (++scr.y < bullet_s.y)
	{
		scr.x = -1;
		while (++scr.x < bullet_s.x)
		{
			texture.x = scr.x * img->width / bullet_s.x;
			texture.y = scr.y * img->height / bullet_s.y;
			color = my_pixel_get(img, texture.x, texture.y);
			if (color != 0x980088 && !active)
				color = 0x969696;
			my_pixel_put(&game->screen, initial_pos.x + scr.x
				+ bullet_index * bullet_s.x, initial_pos.y + scr.y, color);
		}
	}
}

void	draw_bullets(t_game *game)
{
	int		bullet_index;

	bullet_index = -1;
	while (++bullet_index < game->pl.shots_fired)
		draw_bullet(game, &game->img[INDEX_BULLET1_IMAGE], bullet_index, false);
	bullet_index -= 1;
	while (++bullet_index < BULLET_QTY)
		draw_bullet(game, &game->img[INDEX_BULLET1_IMAGE], bullet_index, true);
}
