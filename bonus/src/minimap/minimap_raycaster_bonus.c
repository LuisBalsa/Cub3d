/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_raycaster_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:26:09 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/12 18:20:36 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	hit_minimap(t_player *pl, int x)
{
	if (ft_strchr("12", pl->g->map[pl->map_check.y][pl->map_check.x]))
	{
		pl->g->minimap.hited_tile[x] = pl->map_check;
		return (1);
	}
	return (0);
}

static void	perform_dda_minimap(t_player *pl, int x)
{
	while (!hit_minimap(pl, x))
	{
		if (pl->diagonal_dist.x < pl->diagonal_dist.y)
		{
			pl->diagonal_dist.x += pl->delta_dist.x;
			pl->map_check.x += pl->step.x;
		}
		else
		{
			pl->diagonal_dist.y += pl->delta_dist.y;
			pl->map_check.y += pl->step.y;
		}
		if (pl->map_check.y < 0 || pl->map_check.y >= pl->g->map_height
			|| pl->map_check.x < 0
			|| pl->map_check.x >= (int)ft_strlen(pl->g->map[pl->map_check.y]))
		{
			printf("Error\n");
			break ;
		}
	}
}

static void	init_raycaster(t_player *pl, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)MINIMAP_HITS - 1;
	pl->ray_dir.x = pl->dir.x + pl->plane.x * camera_x;
	pl->ray_dir.y = pl->dir.y + pl->plane.y * camera_x;
	pl->map_check = (t_vi2d){(int)pl->pos.x, (int)pl->pos.y};
	pl->delta_dist.x = 1e30 * (pl->ray_dir.x == 0)
		+ fabs(1.0 / (pl->ray_dir.x + (pl->ray_dir.x == 0)));
	pl->delta_dist.y = 1e30 * (pl->ray_dir.y == 0)
		+ fabs(1.0 / (pl->ray_dir.y + (pl->ray_dir.y == 0)));
	pl->step.x = (pl->ray_dir.x < 0) * -2 + 1;
	pl->diagonal_dist.x = fabs((pl->pos.x - pl->map_check.x)
			- (pl->ray_dir.x > 0)) * pl->delta_dist.x;
	pl->step.y = (pl->ray_dir.y < 0) * -2 + 1;
	pl->diagonal_dist.y = fabs((pl->pos.y - pl->map_check.y)
			- (pl->ray_dir.y > 0)) * pl->delta_dist.y;
}

static void	init_hited_tile(t_game *game)
{
	int	i;

	i = -1;
	while (++i < MINIMAP_HITS)
		game->pl.g->minimap.hited_tile[i] = (t_vi2d){-1, -1};
}

void	minimap_raycaster(t_game *game)
{
	int	x;

	init_hited_tile(game);
	x = -1;
	while (++x < MINIMAP_HITS)
	{
		init_raycaster(&game->pl, x);
		perform_dda_minimap(&game->pl, x);
	}
}
