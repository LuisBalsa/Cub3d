/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game_status_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:47:57 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/19 00:50:28 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_game_status(t_game *game)
{
	t_vi2d	scr;
	t_vi2d	texture;
	t_img	*img;
	int		color;

	if (game->pl.died)
		img = &game->img[INDEX_GAME_OVER_IMAGE];
	else
		img = &game->img[INDEX_YOU_WIN_IMAGE];
	scr.y = -1;
	while (++scr.y < game->screen.height)
	{
		scr.x = -1;
		while (++scr.x < game->screen.width)
		{
			texture.x = scr.x * img->width / game->screen.width;
			texture.y = scr.y * img->height / game->screen.height;
			color = my_pixel_get(img, texture.x, texture.y);
			my_pixel_put(&game->screen, scr.x, scr.y, color);
		}
	}
}
