/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:21:40 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/29 20:55:47 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static void	perform_dda(t_player *pl)
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
		check_hit(pl, &side, pl->map_check, pl->step);
	}
	get_hit_distances(pl, side);
	get_draw_data(pl, &pl->draw);
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
	pl->img_index = -1;
	pl->step.x = (pl->ray_dir.x < 0) * -2 + 1;
	pl->diagonal_dist.x = fabs((pl->pos.x - pl->map_check.x)
			- (pl->ray_dir.x > 0)) * pl->delta_dist.x;
	pl->step.y = (pl->ray_dir.y < 0) * -2 + 1;
	pl->diagonal_dist.y = fabs((pl->pos.y - pl->map_check.y)
			- (pl->ray_dir.y > 0)) * pl->delta_dist.y;
}

int	raycasting(t_game *game)
{
	int	x;

	input_handler(game);
	x = -1;
	while (++x < game->screen.width)
	{
		init_raycaster(&game->pl, x);
		perform_dda(&game->pl);
		draw_walls_and_background(game, &game->pl, x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}
