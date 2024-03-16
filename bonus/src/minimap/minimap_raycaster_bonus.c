/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_raycaster_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:26:09 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/16 21:24:02 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	hit_minimap(t_player *pl, t_minimap *minimap)
{
	if (pl->map_check.y < 0 || pl->map_check.y >= pl->g->map_height
		|| pl->map_check.x < 0 || pl->map_check.x >= \
		(int)ft_strlen(pl->g->map[pl->map_check.y]))
		return (1);
	minimap->map[pl->map_check.y][pl->map_check.x] = \
		pl->g->map[pl->map_check.y][pl->map_check.x];
	minimap->map_hit[pl->map_check.y][pl->map_check.x] = \
		pl->g->map[pl->map_check.y][pl->map_check.x];
	if (!ft_strchr("0126789", pl->g->map[pl->map_check.y][pl->map_check.x]))
		return (0);
	if (ft_strchr("126789", pl->g->map[pl->map_check.y][pl->map_check.x]))
		return (1);
	return (0);
}

static void	perform_dda_minimap(t_player *pl)
{
	while (!hit_minimap(pl, &pl->g->minimap))
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
	}
}

static void	init_raycaster(t_player *pl, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)pl->g->screen.width - 1;
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

void	init_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			map[i][j] = ' ';
	}
}

void	minimap_raycaster(t_game *game)
{
	int	x;

	init_map(game->minimap.map_hit);
	x = -1;
	while (++x < game->screen.width)
	{
		init_raycaster(&game->pl, x);
		perform_dda_minimap(&game->pl);
	}
}
