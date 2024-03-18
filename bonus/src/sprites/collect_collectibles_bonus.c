/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_collectibles_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:53:51 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 14:00:40 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	collect_collectibles(void *sprite)
{
	t_sprite	*collect;

	collect = sprite;
	if ((int)collect->pos.x == (int)collect->g->pl.pos.x
		&& (int)collect->pos.y == (int)collect->g->pl.pos.y)
	{
		collect->visible = false;
		collect->g->map[(int)collect->pos.y][(int)collect->pos.x] = '0';
		collect->g->collected++;
	}
}
