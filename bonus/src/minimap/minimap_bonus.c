/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:56:40 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/13 01:33:36 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	lighten_and_redden_color(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) + 200;
	g = (color >> 8 & 0xFF) + 100;
	b = (color & 0xFF) + 100;
	r = (r > 255) * 255 + (r <= 255) * r;
	g = (g > 255) * 255 + (g <= 255) * g;
	b = (b > 255) * 255 + (b <= 255) * b;
	return (r << 16 | g << 8 | b);
}

static void	get_tile_color(t_game *game, t_minimap *minimap)
{
	t_vi2d	map_pos;

	map_pos = (t_vi2d){minimap->map_pos_index.x + minimap->map_pos_initial.x,
		minimap->map_pos_index.y + minimap->map_pos_initial.y};
	if (map_pos.y < 0 || map_pos.y >= game->map_height
		|| map_pos.x < 0 || map_pos.x >= (int)ft_strlen(game->map[map_pos.y])
		|| game->map[map_pos.y][map_pos.x] == ' ')
		return (minimap->tile_color = -1, (void)0);
	else if (map_pos.y == (int)game->pl.pos.y
		&& map_pos.x == (int)game->pl.pos.x)
		minimap->tile_color = 0x00FF0000;
	else if (game->map[map_pos.y][map_pos.x] == '0')
		minimap->tile_color = 0xE6E6E6;
	else if (game->map[map_pos.y][map_pos.x] == '1')
		minimap->tile_color = 0x00000000;
	else if (game->map[map_pos.y][map_pos.x] == '3')
		minimap->tile_color = 0x0000FF00;
	else if (ft_strchr("245", game->map[map_pos.y][map_pos.x]))
		minimap->tile_color = 0x000000FF;
	else
		minimap->tile_color = 0x00FFFF00;
	if (ft_strchr("01", minimap->map[map_pos.y][map_pos.x]))
		minimap->tile_color = lighten_and_redden_color(minimap->tile_color);
}

static void	draw_map(t_game *game, t_minimap *minimap)
{
	minimap->map_pos_index.y = -1;
	while (++minimap->map_pos_index.y < MINIMAP_H)
	{
		minimap->map_pos_index.x = -1;
		while (++minimap->map_pos_index.x < MINIMAP_W)
		{
			get_tile_color(game, minimap);
			draw_minimap_tile(game, minimap->map_pos_index,
				minimap->tile_color);
		}
	}
}

void	minimap(t_game *game)
{
	if (game->screen.width < (MINIMAP_W + MINIMAP_OFFSET) * MINIMAP_TILE_S
		|| game->screen.height < (MINIMAP_H + MINIMAP_OFFSET) * MINIMAP_TILE_S)
		return ;
	game->minimap.map_pos_initial = (t_vi2d){game->pl.pos.x - MINIMAP_W / 2,
		game->pl.pos.y - MINIMAP_H / 2};
	minimap_raycaster(game);
	draw_map(game, &game->minimap);
}
