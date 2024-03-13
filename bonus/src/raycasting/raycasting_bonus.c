/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:21:40 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/13 02:28:13 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	anim_door_timer(t_game *game)
{
	if (game->anim_door_i
		&& clock() - game->anim_door_time > ANIM_DOOR_DELAY)
	{
		game->anim_door_time = clock();
		game->anim_door_i += game->anim_door_dir * game->time.frame * 200;
		if (game->anim_door_i <= 0 || game->anim_door_i >= TEXTURE_WIDTH)
		{
			game->anim_door_i = 0;
			game->map[game->anim_door.y][game->anim_door.x] = DOOR
				+ (game->anim_door_dir == 1);
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
	pl->img_index = -1;
	pl->step.x = (pl->ray_dir.x < 0) * -2 + 1;
	pl->diagonal_dist.x = fabs((pl->pos.x - pl->map_check.x)
			- (pl->ray_dir.x > 0)) * pl->delta_dist.x;
	pl->step.y = (pl->ray_dir.y < 0) * -2 + 1;
	pl->diagonal_dist.y = fabs((pl->pos.y - pl->map_check.y)
			- (pl->ray_dir.y > 0)) * pl->delta_dist.y;
}

static void	raycasting_sliding_door(t_game *game, t_player *pl, int x)
{
	init_raycaster(pl, x);
	perform_dda_sliding_door(pl);
	if (pl->img_index == INDEX_DOOR_IMAGE)
		draw_walls_and_background(game, pl, x);
	if (pl->hit_x < TEXTURE_WIDTH)
		game->wall_dist[x] = pl->hit_dist;
}

int	raycasting(t_game *game)
{
	int	x;

	game->time.old = game->time.new;
	game->time.new = clock();
	game->time.frame = (game->time.new - game->time.old) / CLOCKS_PER_SEC;
	input_handler(game);
	x = -1;
	while (++x < game->screen.width)
	{
		init_raycaster(&game->pl, x);
		perform_dda(&game->pl);
		draw_walls_and_background(game, &game->pl, x);
		game->wall_dist[x] = game->pl.hit_dist;
		if (game->anim_door_i)
			raycasting_sliding_door(game, &game->pl, x);
	}
	anim_door_timer(game);
	sprites(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}
