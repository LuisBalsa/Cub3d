/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_shooting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:52:19 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/20 22:38:52 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	valid_shot(t_game *g, t_sprite *enemy)
{
	t_vf2d	enemy_dir;
	t_vf2d	map_pos;
	int		i;

	enemy->img_index = INDEX_ENEMY_IMAGE;
	enemy_dir.x = (g->pl.pos.x - enemy->pos.x) / enemy->transform.y / 5;
	enemy_dir.y = (g->pl.pos.y - enemy->pos.y) / enemy->transform.y / 5;
	map_pos = enemy->pos;
	i = 60;
	while (--i)
	{
		map_pos.x += enemy_dir.x;
		map_pos.y += enemy_dir.y;
		if ((int)map_pos.x == (int)g->pl.pos.x
			&& (int)map_pos.y == (int)g->pl.pos.y)
			return (true);
		if (ft_strchr(" 126789", g->map[(int)map_pos.y][(int)map_pos.x]))
			return (false);
	}
	return (true);
}

void	enemy_shooting(t_game *g, t_sprite *enemy)
{
	if (clock() - enemy->anim_time > ANIM_DELAY)
	{
		enemy->anim_time = clock();
		enemy->anim_index += rand() % 2;
		enemy->anim_index %= 5;
		if (enemy->anim_index == 2 && rand() % (int)(enemy->dist / 10 + 1) == 0
			&& valid_shot(g, enemy))
		{
			g->pl.hited = true;
			g->pl.hits_taken++;
			if (g->pl.hits_taken >= ENERGY)
				g->pl.died = true;
		}
		else if (enemy->anim_index == 0 && (rand() % 50 < enemy->dist))
			enemy->mode = ENEMY_WALKING;
	}
}
