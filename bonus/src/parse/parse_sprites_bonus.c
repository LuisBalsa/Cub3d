/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:19:07 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/13 21:34:14 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	sprites_collectable_count(char **map, int *c, int x, int y)
{
	if (ft_strchr(TRANSPOSABLE, map[y][x]) == 0)
		return ;
	if (map[y][x] == 'k')
		(*c)++;
	map[y][x] = 'x';
	if (y > 0)
		sprites_collectable_count(map, c, x, y - 1);
	if (map[y + 1])
		sprites_collectable_count(map, c, x, y + 1);
	if (x > 0)
		sprites_collectable_count(map, c, x - 1, y);
	if (x < (int)ft_strlen(map[y]))
		sprites_collectable_count(map, c, x + 1, y);
}

void	parse_sprites(t_game *game, int x, int y)
{
	char	*sprites;
	int		i;

	if (game->num_sprites == NBR_SPRITES)
		error_exit(game, "Too many sprites");
	game->sprite[game->num_sprites].pos = (t_vf2d){x + 0.5, y + 0.5};
	sprites = ft_strdup(SPRITE_CHARS);
	if (!sprites)
		error_exit(game, "Malloc failed");
	i = -1;
	while (sprites[++i])
		if (game->map[y][x] == sprites[i])
			game->sprite[game->num_sprites].img_index = i + INDEX_SPRITE_IMAGE;
	free(sprites);
	game->sprite[game->num_sprites].anim = (game->map[y][x] == 'f');
	game->num_sprites++;
}
