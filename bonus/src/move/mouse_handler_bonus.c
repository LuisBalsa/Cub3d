/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:39:33 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/04 13:33:37 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	mouse_spinning(t_player *pl, double time, int x)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dir.x;
	old_plane_x = pl->plane.x;
	pl->dir.x = pl->dir.x * cos(time * R_SPD_M * x)
		- pl->dir.y * sin(time * R_SPD_M * x);
	pl->dir.y = old_dir_x * sin(time * R_SPD_M * x)
		+ pl->dir.y * cos(time * R_SPD_M * x);
	pl->plane.x = pl->plane.x * cos(time * R_SPD_M * x)
		- pl->plane.y * sin(time * R_SPD_M * x);
	pl->plane.y = old_plane_x * sin(time * R_SPD_M * x)
		+ pl->plane.y * cos(time * R_SPD_M * x);
}

static void	mouse_pitch(t_player *pl, double time, int y)
{
	pl->pitch += -y * time * PITCH_SPD;
	if (pl->pitch > PITCH)
		pl->pitch = PITCH;
	if (pl->pitch < -PITCH)
		pl->pitch = -PITCH;
}

int	mouse_movement_handler(int x, int y, t_game *game)
{
	t_mouse	*m;

	if (!game->key.esc)
		return (0);
	m = &game->mouse;
	if (x == m->prev_pos.x && y == m->prev_pos.y)
		return (0);
	mouse_spinning(&game->pl, game->time.frame, x - m->prev_pos.x);
	mouse_pitch(&game->pl, game->time.frame, y - m->prev_pos.y);
	mlx_mouse_move(game->mlx, game->win, m->prev_pos.x, m->prev_pos.y);
	return (0);
}

int	mouse_click_handler(int button, int x, int y, t_game *game)
{
	if (button != 1 || game->key.esc)
		return (0);
	game->key.esc = -1;
	game->mouse.pos.x = x;
	game->mouse.pos.y = y;
	game->mouse.prev_pos = game->mouse.pos;
	return (0);
}
