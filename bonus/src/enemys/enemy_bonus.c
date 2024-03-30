/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:09:30 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/29 11:14:22 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"


static void	create_bullets(t_game *game, t_vf2d pos)
{
	t_list		*new;
	t_sprite	*sprite;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		error_exit(game, "Malloc failed");
	sprite->pos = pos;
	sprite->img_index = INDEX_BULLET_IMAGE;
	game->map[(int)pos.y][(int)pos.x] = 'y';
	sprite->visible = true;
	sprite->g = game;
	new = ft_lstnew(sprite);
	if (!new)
		error_exit(game, "Malloc failed");
	ft_lstadd_back(&game->sprites, new);
}

static void	enemy_dying(t_sprite *enemy)
{
	enemy->img_index = INDEX_ENEMY_IMAGE + ENEMY_DYING;
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index++;
		if (enemy->anim_index >= 4)
		{
			enemy->enemy_animated = false;
			enemy->anim_index = 4;
			enemy->g->map[(int)enemy->pos.y][(int)enemy->pos.x] = '0';
			enemy->type = '0';
			if (rand() % 3)
				create_bullets(enemy->g, enemy->pos);
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
	test = (t_vf2d){new_pos.x + enemy_dir.x * 5, new_pos.y + enemy_dir.y * 5};
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
	if (!ft_strchr("0", game->map[(int)(enemy->pos.y)][(int)(enemy->pos.x)]))
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
		while (++i < 3 * enemy->dist)
			move_enemy(game, enemy);
		game->map[(int)enemy->pos.y][(int)enemy->pos.x] = 'e';
		if (enemy->anim_index == 0 && rand() % 2)
			enemy->mode = ENEMY_SHOOTING;
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
		enemy_dying(sprite);
	if (sprite->mode != ENEMY_DYING)
		sprite->enemy_animated = false;
}
