/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:09:30 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/17 18:16:38 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	set_enemy_as_animated(void *sprite)
{
	t_sprite	*enemy;

	enemy = sprite;
	if ((int)enemy->pos.x == (int)enemy->g->enemy.hited.x && \
		(int)enemy->pos.y == (int)enemy->g->enemy.hited.y)
		enemy->animated = true;
}
