/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_sliding_door_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:52:37 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/16 18:11:47 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	hit_door_sliding(t_player *pl, int *side)
{
	pl->img_index = INDEX_DOOR_IMAGE;
	if (*side == 1)
	{
		pl->diagonal_dist.x -= pl->delta_dist.x / 2;
		if (pl->diagonal_dist.x > pl->diagonal_dist.y)
		{
			pl->diagonal_dist.y += pl->delta_dist.y;
			pl->map_check.y += pl->step.y;
			*side = 3;
			pl->img_index = false;
		}
		pl->diagonal_dist.x += pl->delta_dist.x;
	}
	else
	{
		pl->diagonal_dist.y -= pl->delta_dist.y / 2;
		if (pl->diagonal_dist.y > pl->diagonal_dist.x)
		{
			pl->diagonal_dist.x += pl->delta_dist.x;
			pl->map_check.x += pl->step.x;
			*side = 1;
			pl->img_index = false;
		}
		pl->diagonal_dist.y += pl->delta_dist.y;
	}
}

void	check_hit_sliding_door(t_player *pl, int *side, t_vi2d check)
{
	if (ft_strchr("126789", pl->map[check.y][check.x]))
		pl->img_index = false;
	if (pl->map[check.y][check.x] == OPENING_DOOR
		|| pl->map[check.y][check.x] == CLOSING_DOOR)
		hit_door_sliding(pl, side);
}
