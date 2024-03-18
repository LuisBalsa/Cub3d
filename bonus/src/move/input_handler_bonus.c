/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:51:14 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/18 00:48:23 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	linear_movement(t_player *pl, double time, int direction)
{
	t_vf2d	new_pos;
	t_vf2d	test;
	t_vf2d	tolerance;
	char	cell;

	new_pos.x = pl->pos.x + pl->dir.x * time * MV_SPD * direction;
	tolerance.x = TOLERANCE * pl->dir.x * direction;
	new_pos.y = pl->pos.y + pl->dir.y * time * MV_SPD * direction;
	tolerance.y = TOLERANCE * pl->dir.y * direction;
	test = (t_vf2d){new_pos.x + tolerance.x, new_pos.y + tolerance.y};
	if (test.y < 0 || test.y >= pl->g->map_height)
		return ;
	if (test.x < 0 || test.x >= (int)ft_strlen(pl->map[(int)test.y]))
		return ;
	cell = pl->map[(int)(test.y)][(int)pl->pos.x];
	if (ft_strchr(WALKABLE, cell))
		pl->pos.y = new_pos.y;
	cell = pl->map[(int)pl->pos.y][(int)(test.x)];
	if (ft_strchr(WALKABLE, cell))
		pl->pos.x = new_pos.x;
}

static void	strafe_movement(t_player *pl, double time, int direction)
{
	t_vf2d	new_pos;
	t_vf2d	test;
	t_vf2d	tolerance;
	char	cell;

	new_pos.x = pl->pos.x + pl->plane.x * time * MV_SPD * direction;
	tolerance.x = TOLERANCE * pl->plane.x * direction;
	new_pos.y = pl->pos.y + pl->plane.y * time * MV_SPD * direction;
	tolerance.y = TOLERANCE * pl->plane.y * direction;
	test = (t_vf2d){new_pos.x + tolerance.x, new_pos.y + tolerance.y};
	if (test.y < 0 || test.y >= pl->g->map_height)
		return ;
	if (test.x < 0 || test.x >= (int)ft_strlen(pl->map[(int)test.y]))
		return ;
	cell = pl->map[(int)test.y][(int)pl->pos.x];
	if (ft_strchr(WALKABLE, cell))
		pl->pos.y = new_pos.y;
	cell = pl->map[(int)pl->pos.y][(int)test.x];
	if (ft_strchr(WALKABLE, cell))
		pl->pos.x = new_pos.x;
}

static void	spinning(t_player *pl, double time, int direction)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dir.x;
	old_plane_x = pl->plane.x;
	pl->dir.x = pl->dir.x * cos(time * R_SPD * direction)
		- pl->dir.y * sin(time * R_SPD * direction);
	pl->dir.y = old_dir_x * sin(time * R_SPD * direction)
		+ pl->dir.y * cos(time * R_SPD * direction);
	pl->plane.x = pl->plane.x * cos(time * R_SPD * direction)
		- pl->plane.y * sin(time * R_SPD * direction);
	pl->plane.y = old_plane_x * sin(time * R_SPD * direction)
		+ pl->plane.y * cos(time * R_SPD * direction);
}

static void	pitch(t_player *pl, double time, int direction)
{
	pl->pitch += time * PITCH_SPD * direction;
	if (pl->pitch > PITCH)
		pl->pitch = PITCH;
	if (pl->pitch < -PITCH)
		pl->pitch = -PITCH;
}

void	input_handler(t_game *game)
{
	if (game->key.esc >= 1)
		free_game(game);
	if (game->key.w)
		linear_movement(&game->pl, game->time.frame, 1);
	if (game->key.s)
		linear_movement(&game->pl, game->time.frame, -1);
	if (game->key.a)
		strafe_movement(&game->pl, game->time.frame, -1);
	if (game->key.d)
		strafe_movement(&game->pl, game->time.frame, 1);
	if (game->key.left)
		spinning(&game->pl, game->time.frame, -1);
	if (game->key.right)
		spinning(&game->pl, game->time.frame, 1);
	if (game->key.up)
		pitch(&game->pl, game->time.frame, 1);
	if (game->key.down)
		pitch(&game->pl, game->time.frame, -1);
}
