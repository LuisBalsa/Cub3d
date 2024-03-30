/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprite_status_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:53:51 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/30 23:48:27 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	enemy_check(t_game *game, t_sprite *sprite)
{
	if (sprite->type != 'e' || game->minimap.map_hit[(int)sprite->pos.y]
		[(int)sprite->pos.x] != 'e')
		return ;
	if ((int)sprite->pos.x == game->enemy.hited.x
		&& (int)sprite->pos.y == game->enemy.hited.y
		&& sprite->mode != ENEMY_DYING)
	{
		sprite->anim_index = 0;
		sprite->mode = ENEMY_DYING;
		game->enemy.hited = (t_vi2d){0, 0};
	}
	sprite->enemy_animated = true;
}

static void	collectable_check(t_game *game, t_sprite *sprite)
{
	if (!ft_strchr("khy", sprite->type)
		|| (int)sprite->pos.x != (int)game->pl.pos.x
		|| (int)sprite->pos.y != (int)game->pl.pos.y)
		return ;
	sprite->visible = false;
	if (game->map[(int)sprite->pos.y][(int)sprite->pos.x] == 'k')
		game->collected++;
	else if (game->map[(int)sprite->pos.y][(int)sprite->pos.x] == 'h')
	{
		game->pl.hits_taken -= 3;
		if (game->pl.hits_taken < 0)
			game->pl.hits_taken = 0;
	}
	else
	{
		game->pl.shots_fired -= 5;
		if (game->pl.shots_fired < 0)
			game->pl.shots_fired = 0;
	}
	game->map[(int)sprite->pos.y][(int)sprite->pos.x] = '0';
}

void	check_sprite_status(void *sp)
{
	t_sprite	*sprite;
	t_game		*game;

	sprite = sp;
	game = sprite->g;
	enemy_check(game, sprite);
	collectable_check(game, sprite);
}
