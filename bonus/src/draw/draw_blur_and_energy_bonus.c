/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_blur_and_energy_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:32:12 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 00:20:42 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	draw_energy_bar(t_game *game, int index, int color, t_vi2d i_pos)
{
	t_vi2d	pos;
	int		i;
	int		j;

	pos = (t_vi2d){i_pos.x + index * (ENERGY_BAR_W + ENERGY_BAR_SP),
		i_pos.y};
	i = -1;
	while (++i < ENERGY_BAR_H)
	{
		j = -1;
		while (++j < ENERGY_BAR_W)
			my_pixel_put(&game->screen, pos.x + j, pos.y + i, color);
	}
}

void	draw_energy(t_game *game)
{
	int		bar_index;
	t_vi2d	initial_pos;

	initial_pos = (t_vi2d){ENERGY_BAR_OFFSET, game->screen.height
		- ENERGY_BAR_H - ENERGY_BAR_OFFSET};
	bar_index = -1;
	while (++bar_index < 6 - game->pl.hits_taken)
		draw_energy_bar(game, bar_index, 0x00FF00, initial_pos);
	bar_index -= 1;
	while (++bar_index < 6)
		draw_energy_bar(game, bar_index, 0xFF0000, initial_pos);
}

void	draw_hit_blur(t_img *img, t_img *screen)
{
	t_vi2d	scr;
	t_vi2d	texture;
	int		color;

	if (rand() % 2)
		return ;
	scr.y = -1;
	while (++scr.y < screen->height)
	{
		scr.x = -1;
		while (++scr.x < screen->width)
		{
			texture.x = scr.x * img->width / screen->width;
			texture.y = scr.y * img->height / screen->height;
			color = my_pixel_get(img, texture.x, texture.y);
			if (rand() % 3)
				my_pixel_put(screen, scr.x, scr.y, color);
		}
	}
}

