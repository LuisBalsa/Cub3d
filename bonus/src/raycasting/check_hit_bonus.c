/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:52:37 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/13 04:37:08 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	hit_door_closed(t_player *pl, int *side)
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
			pl->img_index++;
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
			pl->img_index++;
		}
		pl->diagonal_dist.y += pl->delta_dist.y;
	}
}

static void	hit_door_open(t_player *pl, int *side)
{
	if (*side == 1)
	{
		if (pl->diagonal_dist.x > pl->diagonal_dist.y)
		{
			pl->diagonal_dist.y += pl->delta_dist.y;
			pl->map_check.y += pl->step.y;
			*side = 3;
			pl->img_index = INDEX_DOOR_IMAGE + 1;
		}
	}
	else
	{
		if (pl->diagonal_dist.y > pl->diagonal_dist.x)
		{
			pl->diagonal_dist.x += pl->delta_dist.x;
			pl->map_check.x += pl->step.x;
			*side = 1;
			pl->img_index = INDEX_DOOR_IMAGE + 1;
		}
	}
}

void	check_hit(t_player *pl, int *side, t_vi2d check)
{
	t_vi2d	step;

	step = pl->step;
	if (pl->map[check.y][check.x] == WALL)
		pl->img_index = *side - (*side == 1 && step.x < 0)
			- (*side == 3 && step.y < 0);
	if (pl->map[check.y][check.x] == DOOR)
		hit_door_closed(pl, side);
	if (pl->map[check.y][check.x] == OPEN_DOOR
		|| pl->map[check.y][check.x] == OPENING_DOOR
		|| pl->map[check.y][check.x] == CLOSING_DOOR)
		hit_door_open(pl, side);
	if (((pl->map[check.y][check.x - step.x] == OPEN_DOOR && \
		pl->map[check.y][check.x - 2 * step.x] == WALL && *side == 1) ||
		(pl->map[check.y - step.y][check.x] == OPEN_DOOR && \
		pl->map[check.y - 2 * step.y][check.x] == WALL && *side == 3)) \
		&& pl->map[check.y][check.x] == WALL)
		pl->img_index = INDEX_DOOR_IMAGE + 1;
}
