/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:09:30 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/17 20:31:47 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	enemy_dying(t_game *game, t_sprite *enemy)
{
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index++;
		if (enemy->anim_index == 4)
		{
			enemy->enemy_animated = false;
			game->map[(int)enemy->pos.y][(int)enemy->pos.x] = '0';
		}
	}
}

/* static void	check_hit_player(t_game *game, t_sprite *enemy)
{
} */

static void	enemy_shooting(t_game *game, t_sprite *enemy)
{
	(void)game;
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index++;
		enemy->anim_index -= (enemy->anim_index == 1) * rand() % 2;
		enemy->anim_index -= (enemy->anim_index == 2) * rand() % 2;
		enemy->anim_index -= (enemy->anim_index == 4) * rand() % 2;
		enemy->anim_index %= 5;
/* 		if (enemy->anim_index == 2)
			check_hit_player(game, enemy); */
	}
}

void	animate_enemy(t_game *game, t_sprite *sprite)
{
	if (!sprite->enemy_animated)
		return ;
	if (sprite->mode == ENEMY_SHOOTING)
		enemy_shooting(game, sprite);
/* 	else if (sprite->mode == ENEMY_WALKING)
		enemy_walking(game, sprite); */
	else
		enemy_dying(game, sprite);
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
