/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:21:40 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 03:05:28 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	anim_door_hit_blur(t_game *g)
{
	if (g->map[g->anim_door.y][g->anim_door.x] == OPEN_DOOR
		&& (g->minimap.map_hit[g->anim_door.y][g->anim_door.x] != OPEN_DOOR
		|| (fabs(g->anim_door.x - g->pl.pos.x) > 2
		|| fabs(g->anim_door.y - g->pl.pos.y) > 2)))
	{
		g->map[g->anim_door.y][g->anim_door.x] = CLOSING_DOOR;
		g->anim_door_i = TEXTURE_WIDTH;
		g->anim_door_dir = -1;
	}
	if (g->pl.hited)
	{
		g->pl.hited += g->time.frame * HIT_BLUR_SPD;
		if (g->pl.hited >= 2)
			g->pl.hited = 0;
	}
	if (!g->anim_door_i)
		return ;
	g->anim_door_i += g->anim_door_dir * g->time.frame * DOOR_SPD;
	if (g->anim_door_i <= 0 || g->anim_door_i >= TEXTURE_WIDTH)
	{
		g->anim_door_i = 0;
		g->map[g->anim_door.y][g->anim_door.x] = DOOR
			+ (g->anim_door_dir == 1);
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

static void	check_collectables(t_game *game)
{
	char		*collectibles;
	t_list		*tmp;

	if (!game->collectibles_found)
		return ;
	if (game->map[(int)game->pl.pos.y][(int)game->pl.pos.x] == 'k')
	{
		game->map[(int)game->pl.pos.y][(int)game->pl.pos.x] = '0';
		game->collected++;
		tmp = ft_lstlast(game->sprites);
		((t_sprite *)tmp->content)->visible = false;
	}
	if (game->nbr_collectibles == game->collected)
	{
		mlx_string_put(game->mlx, game->win, MINIMAP_W + 200, 50, 0x000000,
			"Congratulations! You collected all possible keys!");
	}
	else
	{
		mlx_string_put(game->mlx, game->win, MINIMAP_W + 200, 50, 0x000000,
			"Collect the remaining possible keys:");
		mlx_string_put(game->mlx, game->win, MINIMAP_W + 450, 50, 0x000000,
			collectibles = ft_itoa(game->nbr_collectibles - game->collected));
		free(collectibles);
	}
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
	sprites(game);
	minimap(game);
	anim_door_hit_blur(game);
	draw_energy_and_keys(game);
	if (game->pl.hited)
		draw_hit_blur(&game->img[INDEX_HIT_IMAGE], &game->screen);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	check_collectables(game);
	return (0);
}
