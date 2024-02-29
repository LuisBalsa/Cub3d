/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:40:49 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/29 21:07:47 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
