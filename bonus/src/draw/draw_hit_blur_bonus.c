/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit_blur_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:32:12 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/17 22:58:56 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

