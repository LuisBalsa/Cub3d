/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hands_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:38:44 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 15:52:06 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_hands(t_game *game)
{
	t_vi2d	scr;
	t_vi2d	texture;
	t_img	*img;
	int		color;

	img = &game->img[INDEX_HANDS_IMAGE];
	scr.y = -1;
	while (++scr.y < game->screen.height)
	{
		scr.x = -1;
		while (++scr.x < game->screen.width)
		{
			texture.x = scr.x * img->width / game->screen.width;
			texture.y = scr.y * img->height / game->screen.height;
			color = my_pixel_get(&game->img[INDEX_HANDS_IMAGE
					+ game->pl.fire * game->anim_index], texture.x, texture.y);
			my_pixel_put(&game->screen, scr.x, scr.y, color);
		}
	}
}
