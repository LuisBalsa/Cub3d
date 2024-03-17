/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shot_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:24 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/17 17:20:32 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	set_enemy_as_hited(void *sprite)
{
	t_sprite	*enemy;

	enemy = sprite;
	if ((int)enemy->pos.x == (int)enemy->g->enemy.hited.x && \
		(int)enemy->pos.y == (int)enemy->g->enemy.hited.y)
	{
		enemy->visible = false;
		enemy->g->map[(int)enemy->pos.y][(int)enemy->pos.x] = '0';
	}
}

static int	enemy_hited(t_game *game)
{
	t_vi2d	map_pos;

	game->enemy.hited = game->pl.pos;
	while (1)
	{
		game->enemy.hited.x += game->pl.dir.x;
		game->enemy.hited.y += game->pl.dir.y;
		map_pos = (t_vi2d){(int)game->enemy.hited.x, (int)game->enemy.hited.y};
		if (ft_strchr("12456789", game->map[map_pos.y][map_pos.x]))
			break ;
		if (game->map[map_pos.y][map_pos.x] == 'E')
			return (1);
	}
	return (0);
}

void	check_shot(t_game *game)
{
	if (enemy_hited(game))
		ft_lstiter(game->sprites, set_enemy_as_hited);
}
