/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:09:30 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/17 19:19:40 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	enemy_shooting(t_game *game, t_sprite *sprite)
{
	(void)game;
	if (clock() - sprite->anim_time > ANIM_DELAY)
	{
		sprite->anim_time = clock();
		sprite->anim_index++;
		sprite->anim_index -= (sprite->anim_index == 1) * rand() % 2;
		if (sprite->anim_index == 5)
		{
			sprite->anim_index = 0;
		}
	}
}

void	animate_enemy(t_game *game, t_sprite *sprite)
{
	if (!sprite->enemy_animated)
		return ;
	if (sprite->mode == ENEMY_SHOOTING)
		enemy_shooting(game, sprite);
/* 	else if (sprite->mode == ENEMY_WALKING)
		enemy_walking(game, sprite);
	else
		enemy_dying(game, sprite); */
}

void	set_enemy_as_animated(void *sprite)
{
	t_sprite	*enemy;

	enemy = sprite;
	if ((int)enemy->pos.x == (int)enemy->g->enemy.hited.x && \
		(int)enemy->pos.y == (int)enemy->g->enemy.hited.y)
	{
		enemy->enemy_animated = true;
		enemy->anim_index = rand() % 5;
	}
}
