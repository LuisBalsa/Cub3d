/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:09:30 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 13:45:40 by luide-so         ###   ########.fr       */
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
		if (enemy->anim_index >= 4)
		{
			enemy->enemy_animated = false;
			enemy->anim_index = 4;
			enemy->pos = (t_vf2d){(int)enemy->pos.x + 0.5,
				(int)enemy->pos.y + 0.5};
		}
	}
}

static void	move_enemy(t_game *game, t_sprite *enemy)
{
	t_vf2d	new_pos;
	t_vf2d	old_pos;
	t_vf2d	test;
	t_vf2d	enemy_dir;

	old_pos = enemy->pos;
	enemy_dir.x = (game->pl.pos.x - enemy->pos.x) / enemy->dist / 2;
	enemy_dir.y = (game->pl.pos.y - enemy->pos.y) / enemy->dist / 2;
	new_pos.x = enemy->pos.x + enemy_dir.x * game->time.frame;
	new_pos.y = enemy->pos.y + enemy_dir.y * game->time.frame;
	test = (t_vf2d){new_pos.x + enemy_dir.x * 30, new_pos.y + enemy_dir.y * 30};
	if (test.y < 0 || test.y >= game->map_height)
		return ;
	if (test.x < 0 || test.x >= (int)ft_strlen(game->map[(int)test.y]))
		return ;
	if (ft_strchr("0", game->map[(int)test.y][(int)enemy->pos.x])
		&& (test.y != game->pl.pos.y || enemy->pos.x != game->pl.pos.x))
		enemy->pos.y = new_pos.y;
	if (ft_strchr("0", game->map[(int)enemy->pos.y][(int)test.x])
		&& (enemy->pos.y != game->pl.pos.y || test.x != game->pl.pos.x))
		enemy->pos.x = new_pos.x;
	if (!ft_strchr("0", game->map[(int)(enemy->pos.y + enemy_dir.y)]
		[(int)(enemy->pos.x + enemy_dir.x)]))
		enemy->pos = old_pos;
}

static void	enemy_walking(t_game *game, t_sprite *enemy)
{
	int	i;

	enemy->img_index = INDEX_ENEMY_IMAGE + ENEMY_WALKING;
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index++;
		enemy->anim_index %= 5;
		i = -1;
		game->map[(int)enemy->pos.y][(int)enemy->pos.x] = '0';
		while (++i < 2 * enemy->dist)
			move_enemy(game, enemy);
		game->map[(int)enemy->pos.y][(int)enemy->pos.x] = 'e';
		if (enemy->anim_index == 0 && rand() % 2)
			enemy->mode = ENEMY_SHOOTING;
	}
}

static void	enemy_shooting(t_game *g, t_sprite *enemy)
{
	enemy->img_index = INDEX_ENEMY_IMAGE;
	g->map[(int)enemy->pos.y][(int)enemy->pos.x] = 'e';
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
