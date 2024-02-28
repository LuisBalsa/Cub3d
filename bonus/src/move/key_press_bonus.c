/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:40:49 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/28 10:54:22 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	linear_movement(t_player *pl, int direction)
{
	t_vf2d	new_pos;
	char	cell;

	new_pos.x = pl->pos.x + pl->dir.x * MV_SPD * direction;
	new_pos.y = pl->pos.y + pl->dir.y * MV_SPD * direction;
	cell = pl->map[(int)new_pos.y][(int)pl->pos.x];
	if (cell == '0' || cell == '3')
		pl->pos.y = new_pos.y;
	cell = pl->map[(int)pl->pos.y][(int)new_pos.x];
	if (cell == '0' || cell == '3')
		pl->pos.x = new_pos.x;
}

static void	strafe_movement(t_player *pl, int direction)
{
	t_vf2d	new_pos;
	char	cell;

	new_pos.x = pl->pos.x + pl->plane.x * MV_SPD * direction;
	new_pos.y = pl->pos.y + pl->plane.y * MV_SPD * direction;
	cell = pl->map[(int)new_pos.y][(int)pl->pos.x];
	if (cell == '0' || cell == '3')
		pl->pos.y = new_pos.y;
	cell = pl->map[(int)pl->pos.y][(int)new_pos.x];
	if (cell == '0' || cell == '3')
		pl->pos.x = new_pos.x;
}

static void	spinning(t_player *pl, int direction)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dir.x;
	old_plane_x = pl->plane.x;
	pl->dir.x = pl->dir.x * COS - pl->dir.y * SIN * direction;
	pl->dir.y = old_dir_x * SIN * direction + pl->dir.y * COS;
	pl->plane.x = pl->plane.x * COS - pl->plane.y * SIN * direction;
	pl->plane.y = old_plane_x * SIN * direction + pl->plane.y * COS;
}

static void	move(t_game *game)
{
	if (game->key.w)
		linear_movement(&game->pl, 1);
	if (game->key.s)
		linear_movement(&game->pl, -1);
	if (game->key.a)
		strafe_movement(&game->pl, -1);
	if (game->key.d)
		strafe_movement(&game->pl, 1);
	if (game->key.left)
		spinning(&game->pl, -1);
	if (game->key.right)
		spinning(&game->pl, 1);
	raycasting(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->key.w = 1;
	else if (keycode == A)
		game->key.a = 1;
	else if (keycode == S)
		game->key.s = 1;
	else if (keycode == D)
		game->key.d = 1;
	else if (keycode == LEFT)
		game->key.left = 1;
	else if (keycode == RIGHT)
		game->key.right = 1;
	else if (keycode == ESC)
		free_game(game);
	else
		return (0);
	move(game);
	return (0);
}
