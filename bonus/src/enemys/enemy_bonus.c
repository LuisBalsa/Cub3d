/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:09:30 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 02:29:53 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	enemy_dying(t_game *game, t_sprite *enemy)
{
	enemy->img_index = INDEX_ENEMY_IMAGE + ENEMY_DYING;
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index++;
		game->map[(int)enemy->pos.y][(int)enemy->pos.x] = '0';
		if (enemy->anim_index == 4)
			enemy->enemy_animated = false;
	}
}

static void	enemy_walking(t_game *game, t_sprite *enemy)
{
	(void)game;
	enemy->img_index = INDEX_ENEMY_IMAGE + ENEMY_WALKING;
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index++;
		enemy->anim_index %= 5;
		if (enemy->anim_index == 0 && rand() % 2)
			enemy->mode = ENEMY_SHOOTING;
	}
}

static void	enemy_shooting(t_game *g, t_sprite *enemy)
{
	enemy->img_index = INDEX_ENEMY_IMAGE;
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index += rand() % 2;
		enemy->anim_index %= 5;
		if (enemy->anim_index == 2 && rand() % (int)ceil(enemy->dist / 3) == 0)
		{
			g->pl.hited = true;
			g->pl.hits_taken++;
		}
		else if (enemy->anim_index == 0
			&& g->minimap.map_hit[(int)enemy->pos.y][(int)enemy->pos.x] != 'e')
			enemy->enemy_animated = false;
		else if (enemy->anim_index == 0
			&& (rand() % 20 == 0 || enemy->dist > 30))
			enemy->mode = ENEMY_WALKING;
	}
}

void	animate_enemy(t_game *game, t_sprite *sprite)
{
	if (!sprite->enemy_animated)
		return ;
	if (sprite->mode == ENEMY_SHOOTING)
		enemy_shooting(game, sprite);
	else if (sprite->mode == ENEMY_WALKING)
		enemy_walking(game, sprite);
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
		if (enemy->enemy_animated)
			return ;
		enemy->enemy_animated = true;
		enemy->anim_index = rand() % 5;
	}
}
