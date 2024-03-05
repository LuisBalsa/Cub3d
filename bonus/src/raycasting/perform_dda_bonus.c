/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:44:53 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/05 11:35:35 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	get_hit_distances(t_player *pl, int side)
{
	double	hit_x;

	if (side == 1)
		pl->hit_dist = pl->diagonal_dist.x - pl->delta_dist.x;
	else
		pl->hit_dist = pl->diagonal_dist.y - pl->delta_dist.y;
	if (side == 1)
		hit_x = pl->pos.y + pl->hit_dist * pl->ray_dir.y;
	else
		hit_x = pl->pos.x + pl->hit_dist * pl->ray_dir.x;
	hit_x -= floor(hit_x);
	pl->hit_x = (int)(hit_x * (double)TEXTURE_WIDTH);
	if (pl->img_index == INDEX_DOOR_IMAGE)
		return ;
	if (side == 1 && pl->ray_dir.x < 0)
		pl->hit_x = TEXTURE_WIDTH - pl->hit_x - 1;
	if (side == 3 && pl->ray_dir.y > 0)
		pl->hit_x = TEXTURE_WIDTH - pl->hit_x - 1;
}

static void	get_draw_data(t_player *pl, t_draw *draw)
{
	int		line_height;

	line_height = fabs((double)SCREEN_HEIGHT / pl->hit_dist);
	draw->start = SCREEN_HEIGHT / 2 - line_height / 2 + pl->pitch;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = SCREEN_HEIGHT / 2 + line_height / 2 + pl->pitch;
	if (draw->end >= SCREEN_HEIGHT)
		draw->end = SCREEN_HEIGHT - 1;
	draw->step = 1.0 * TEXTURE_HEIGHT / line_height;
	draw->pos = (draw->start - pl->pitch - (double)SCREEN_HEIGHT / 2
			+ (double)line_height / 2) * draw->step;
}

void	perform_dda_sliding_door(t_player *pl)
{
	int		side;

	side = 0;
	while (pl->img_index == -1)
	{
		if (pl->diagonal_dist.x < pl->diagonal_dist.y)
		{
			side = 1;
			pl->diagonal_dist.x += pl->delta_dist.x;
			pl->map_check.x += pl->step.x;
		}
		else
		{
			side = 3;
			pl->diagonal_dist.y += pl->delta_dist.y;
			pl->map_check.y += pl->step.y;
		}
		check_hit_sliding_door(pl, &side, pl->map_check);
	}
	if (pl->img_index == INDEX_DOOR_IMAGE)
	{
		get_hit_distances(pl, side);
		pl->hit_x += pl->g->anim_door_i;
		get_draw_data(pl, &pl->draw);
	}
}

void	perform_dda(t_player *pl)
{
	int		side;

	side = 0;
	while (pl->img_index == -1)
	{
		if (pl->diagonal_dist.x < pl->diagonal_dist.y)
		{
			side = 1;
			pl->diagonal_dist.x += pl->delta_dist.x;
			pl->map_check.x += pl->step.x;
		}
		else
		{
			side = 3;
			pl->diagonal_dist.y += pl->delta_dist.y;
			pl->map_check.y += pl->step.y;
		}
		check_hit(pl, &side, pl->map_check);
	}
	get_hit_distances(pl, side);
	get_draw_data(pl, &pl->draw);
}
