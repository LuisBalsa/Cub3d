/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:56:40 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/12 13:02:24 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* static void	draw_player(t_game *game, t_minimap *minimap)
{
} */

static void	get_tile_color(t_game *game, t_minimap *minimap)
{
	t_vi2d	map_pos;

	map_pos = (t_vi2d){minimap->map_pos_index.x + minimap->map_pos_initial.x,
		minimap->map_pos_index.y + minimap->map_pos_initial.y};
	if (map_pos.y < 0 || map_pos.y >= game->map_height
		|| map_pos.x < 0 || map_pos.x >= (int)ft_strlen(game->map[map_pos.y])
		|| game->map[map_pos.y][map_pos.x] == ' ')
		minimap->tile_color = -1;
	else if (map_pos.y == (int)game->pl.pos.y
		&& map_pos.x == (int)game->pl.pos.x)
		minimap->tile_color = 0x00FF0000;
	else if (game->map[map_pos.y][map_pos.x] == '0')
		minimap->tile_color = 0x00FFFFFF;
	else if (game->map[map_pos.y][map_pos.x] == '1')
		minimap->tile_color = 0x00000000;
	else if (game->map[map_pos.y][map_pos.x] == '3')
		minimap->tile_color = 0x0000FF00;
	else if (ft_strchr("245", game->map[map_pos.y][map_pos.x]))
		minimap->tile_color = 0x000000FF;
	else
		minimap->tile_color = 0x00FFFF00;
}

static void	draw_map(t_game *game, t_minimap *minimap)
{
	minimap->map_pos_index.y = -1;
	while (++minimap->map_pos_index.y < MINIMAP_HEIGHT)
	{
		minimap->map_pos_index.x = -1;
		while (++minimap->map_pos_index.x < MINIMAP_WIDTH)
		{
			get_tile_color(game, minimap);
			draw_minimap_tile(game, minimap->map_pos_index,
				minimap->tile_color);
		}
	}
}

void	minimap(t_game *game)
{
	if (game->screen.width < MINIMAP_WIDTH * MINIMAP_TILE_SIZE
		|| game->screen.height < MINIMAP_HEIGHT * MINIMAP_TILE_SIZE)
		return ;
	game->minimap.map_pos_initial = (t_vi2d){game->pl.pos.x - MINIMAP_WIDTH / 2,
		game->pl.pos.y - MINIMAP_HEIGHT / 2};
	draw_map(game, &game->minimap);
//	draw_player(game, &game->minimap);
}
