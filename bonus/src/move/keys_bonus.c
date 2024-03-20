/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:40:49 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/20 11:27:57 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	check_hited_tile(t_game *game)
{
	t_vf2d	map_pos;

	map_pos = game->pl.pos;
	while (!ft_strchr("e 126789", game->map[(int)map_pos.y][(int)map_pos.x])
			|| !game->map[(int)map_pos.y][(int)map_pos.x])
	{
		map_pos.x += game->pl.dir.x;
		map_pos.y += game->pl.dir.y;
	}
	game->enemy.hited = (t_vi2d){(int)map_pos.x, (int)map_pos.y};
}

static void	shot(t_game *game)
{
	if (game->pl.shots_fired >= BULLET_QTY)
		return ;
	game->pl.fire = true;
	game->anim_index = 0;
	game->pl.shots_fired++;
	check_hited_tile(game);
}

static void	door(t_game *game)
{
	int			x;
	int			y;
	t_player	*pl;

	pl = &game->pl;
	x = (int)(pl->pos.x + pl->dir.x);
	y = (int)(pl->pos.y + pl->dir.y);
	if (x == (int)pl->pos.x && y == (int)pl->pos.y)
		return ;
	if (pl->map[y][x] == DOOR && !game->anim_door_i)
	{
		pl->map[y][x] = OPENING_DOOR;
		game->anim_door_i = 1;
		game->anim_door_dir = 1;
		game->anim_door = (t_vi2d){x, y};
	}
	else if (pl->map[y][x] == OPEN_DOOR && !game->anim_door_i)
	{
		pl->map[y][x] = CLOSING_DOOR;
		game->anim_door_i = TEXTURE_WIDTH;
		game->anim_door_dir = -1;
		game->anim_door = (t_vi2d){x, y};
	}
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->key.w = 0;
	else if (keycode == A)
		game->key.a = 0;
	else if (keycode == S)
		game->key.s = 0;
	else if (keycode == D)
		game->key.d = 0;
	else if (keycode == LEFT)
		game->key.left = 0;
	else if (keycode == RIGHT)
		game->key.right = 0;
	else if (keycode == UP)
		game->key.up = 0;
	else if (keycode == DOWN)
		game->key.down = 0;
	else if (keycode == ESC)
		game->key.esc += 1;
	return (0);
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
	else if (keycode == E)
		door(game);
	else if (keycode == SPACEBAR)
		shot(game);
	else if (keycode == LEFT)
		game->key.left = 1;
	else if (keycode == RIGHT)
		game->key.right = 1;
	else if (keycode == UP)
		game->key.up = 1;
	else if (keycode == DOWN)
		game->key.down = 1;
	return (0);
}
