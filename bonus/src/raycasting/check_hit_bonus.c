/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:52:37 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/27 15:40:41 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* void	door_adjustment(t_game *game)
{
	game->hit = 'D';
	if (game->side == '0')
	{
		game->side_dist_x -= game->delta_dist_x / 2;
		if (game->side_dist_x > game->side_dist_y)
		{
			game->side_dist_y += game->delta_dist_y;
			game->map_y += game->step_y;
			game->side = '1';// retirando fica a parede oca
			game->hit = '1'; // retirando fica a imagem do aro da porta
		}
		game->side_dist_x += game->delta_dist_x;
	}
	else if (game->side == '1')
	{
		game->side_dist_y -= game->delta_dist_y / 2;
		if (game->side_dist_y > game->side_dist_x)
		{
			game->side_dist_x += game->delta_dist_x;
			game->map_x += game->step_x;
			game->side = '0';// retirando fica a parede oca
			game->hit = '1'; // retirando fica a imagem do aro da porta
		}
		game->side_dist_y += game->delta_dist_y;
	}
} */

/* static void	hit_door_closed(t_player *pl, int side)
{
	pl->img_index = INDEX_DOOR_IMAGE;
	if (side == 1)
	{
		pl->diagonal_dist.x -= pl->delta_dist.x / 2;
		if (pl->diagonal_dist.x > pl->diagonal_dist.y)
		{
			pl->diagonal_dist.y += pl->delta_dist.y;
			pl->map_check.y += pl->step.y;
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
			pl->img_index++;
		}
		pl->diagonal_dist.y += pl->delta_dist.y;
	}
} */

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

void	check_hit(t_player *pl, int *side, t_vi2d check, t_vi2d step)
{
	if (pl->map[check.y][check.x] == '1')
		pl->img_index = *side - (*side == 1 && step.x < 0)
			- (*side == 3 && step.y < 0);
	if (pl->map[check.y][check.x] == '2')
		hit_door_closed(pl, side);
	if (pl->map[check.y][check.x] == '3')
		hit_door_open(pl, side);
}
