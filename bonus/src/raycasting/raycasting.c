/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:21:40 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/24 23:52:41 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d_bonus.h"

static void	check_hit(t_player *pl, int side, t_vi2d check, t_vi2d step)
{
	if (pl->map[check.y][check.x] == '1')
		pl->img_index = side - (side == 1 && step.x < 0) - (side == 3 && step.y < 0);
	if (pl->map[check.y][check.x] == '2')
		pl->img_index = INDEX_DOOR_IMAGE;
}

static void	get_hit_distances(t_player *pl, int side)
{
	double	hit_x;

	if (pl->diagonal_dist.x < pl->diagonal_dist.y)
		pl->hit_dist = pl->diagonal_dist.x - pl->delta_dist.x;
	else
		pl->hit_dist = pl->diagonal_dist.y - pl->delta_dist.y;
	if (side == 1)
		hit_x = pl->pos.y + pl->hit_dist * pl->ray_dir.y;
	else
		hit_x = pl->pos.x + pl->hit_dist * pl->ray_dir.x;
	hit_x -= floor(hit_x);
	pl->hit_x = (int)(hit_x * (double)TEXTURE_WIDTH);
	if (side == 1 && pl->ray_dir.y > 0)
		pl->hit_x = TEXTURE_WIDTH - pl->hit_x - 1;
	if (side == 3 && pl->ray_dir.x < 0)
		pl->hit_x = TEXTURE_WIDTH - pl->hit_x - 1;
}

static void	calculate_draw_data(t_player *pl, t_draw *draw)
{
	int		line_height;

	line_height = (int)(SCREEN_HEIGHT / pl->hit_dist);
	draw->start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw->end >= SCREEN_HEIGHT)
		draw->end = SCREEN_HEIGHT - 1;
	draw->step = 1.0 * TEXTURE_HEIGHT / line_height;
	draw->pos = (draw->start - (double)SCREEN_HEIGHT / 2 +
		(double)line_height / 2) * draw->step;
}

static void	perform_dda(t_player *pl)
{
	int		side;

	side = 0;
	while (pl->img_index == -1)
	{
		if (pl->diagonal_dist.x < pl->diagonal_dist.y)
		{
			pl->diagonal_dist.x += pl->delta_dist.x;
			pl->map_check.x += pl->step.x;
			side = 1;
		}
		else
		{
			pl->diagonal_dist.y += pl->delta_dist.y;
			pl->map_check.y += pl->step.y;
			side = 3;
		}
		check_hit(pl, side, pl->map_check, pl->step);
	}
	get_hit_distances(pl, side);
	calculate_draw_data(pl, &pl->draw);
}

static void	init_raycaster(t_player *pl, int x)
{
	pl->plane.x = 2 * x / (double)pl->g->screen.width - 1;
	pl->ray_dir.x = pl->dir.x + pl->plane.x * pl->plane.x;
	pl->ray_dir.y = pl->dir.y + pl->plane.y * pl->plane.x;
	pl->map_check = (t_vi2d){(int)pl->pos.x, (int)pl->pos.y};
	pl->delta_dist.x = 1e30 * (pl->ray_dir.x == 0) +
		fabs(1.0 / (pl->ray_dir.x + (pl->ray_dir.x == 0)));
	pl->delta_dist.y = 1e30 * (pl->ray_dir.y == 0) +
		fabs(1.0 / (pl->ray_dir.y + (pl->ray_dir.y == 0)));
	pl->img_index = -1; // ????
	pl->step.x = (pl->ray_dir.x < 0) * -2 + 1;
	pl->diagonal_dist.x = fabs(pl->pos.x - pl->map_check.x +
		(pl->ray_dir.x < 0)) * pl->delta_dist.x;
	pl->step.y = (pl->ray_dir.y < 0) * -2 + 1;
	pl->diagonal_dist.y = fabs(pl->pos.y - pl->map_check.y +
		(pl->ray_dir.y < 0)) * pl->delta_dist.y;
}

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < game->screen.width)
	{
		y = -1;
		while (++y < game->screen.height / 2)
			my_pixel_put(&game->screen, x, y, game->color[clg]);
		y--;
		while (++y < game->screen.height)
			my_pixel_put(&game->screen, x, y, game->color[flr]);
	}
}

void	raycasting(t_game *game)
{
	int		x;

	draw_background(game);
	x = -1;
	while (++x < game->screen.width)
	{
		init_raycaster(&game->pl, x);
		perform_dda(&game->pl);
		draw_wall(game, x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
