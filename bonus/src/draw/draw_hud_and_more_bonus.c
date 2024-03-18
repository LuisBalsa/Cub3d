/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_and_more_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:32:12 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 17:53:21 by luide-so         ###   ########.fr       */
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

static void	draw_key(t_game *game, t_img *img, int index, bool gray)
{
	t_vi2d	scr;
	t_vi2d	texture;
	t_vi2d	initial_pos;
	int		color;

	initial_pos = (t_vi2d){game->screen.width - KEYS_OFFSET,
		- KEYS_OFFSET + KEYS_DIST};
	scr.y = -1;
	while (++scr.y < KEYS_SIZE)
	{
		scr.x = -1;
		while (++scr.x < KEYS_SIZE)
		{
			texture.x = scr.x * img->width / KEYS_SIZE;
			texture.y = scr.y * img->height / KEYS_SIZE;
			color = my_pixel_get(img, texture.x, texture.y);
			if (color != 0x980088 && gray)
				color = 0x969696;
			my_pixel_put(&game->screen, initial_pos.x + scr.x,
				initial_pos.y + scr.y + index * KEYS_DIST, color);
		}
	}
}

static void	draw_keys(t_game *game)
{
	int		key_index;

	key_index = -1;
	while (++key_index < game->collected)
		draw_key(game, &game->img[INDEX_SPRITE_IMAGE + 3], key_index, false);
	key_index -= 1;
	while (++key_index < game->nbr_collectibles)
		draw_key(game, &game->img[INDEX_SPRITE_IMAGE + 3], key_index, true);
}

static void	draw_hit_blur(t_img *img, t_img *screen)
{
	t_vi2d	scr;
	t_vi2d	texture;
	int		color;

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

void	draw_hud_and_more(t_game *game)
{
	int		bar_index;
	t_vi2d	initial_pos;

	draw_hands(game);
	initial_pos = (t_vi2d){ENERGY_BAR_OFFSET, game->screen.height
		- ENERGY_BAR_H - ENERGY_BAR_OFFSET};
	bar_index = -1;
	while (++bar_index < ENERGY - game->pl.hits_taken)
		draw_energy_bar(game, bar_index, 0x00FF00, initial_pos);
	bar_index -= 1;
	while (++bar_index < ENERGY)
		draw_energy_bar(game, bar_index, 0xFF0000, initial_pos);
	if (game->collectibles_found)
		draw_keys(game);
	if (game->pl.hited && rand() % 2)
		draw_hit_blur(&game->img[INDEX_HIT_IMAGE], &game->screen);
}

