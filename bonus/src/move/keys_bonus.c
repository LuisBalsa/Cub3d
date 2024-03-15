/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:40:49 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/15 09:50:19 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	print_sprites(t_game *game) //testes
{
	int	i;

	i = -1;
	while (++i < game->num_sprites)
	{
		printf("\nSprite %d pos x: %f\n", i, game->sprite[i].pos.x);
		printf("Sprite %d pos y: %f\n", i, game->sprite[i].pos.y);
		printf("Sprite %d img index: %d\n", i, game->sprite[i].img_index);
		printf("Sprite %d dist: %f\n", i, game->sprite[i].dist);
		printf("Sprite %d transform y: %f\n", i, game->sprite[i].transform.y);
		printf("Sprite %d screen x: %d\n", i, game->sprite[i].screen_x);
		printf("Sprite %d height: %d\n", i, game->sprite[i].height);
		printf("Sprite %d draw start x: %d\n", i, game->sprite[i].draw_start.x);
		if (game->sprite[i].draw_start.x < game->screen.width)
			printf("Wall dist x: %f\n", game->wall_dist[game->sprite[i].draw_start.x]);
		printf("Sprite %d draw start y: %d\n", i, game->sprite[i].draw_start.y);
	}
}

static void	print_debug(t_game *game) //testes
{
	printf("Player pos x: %f\n", game->pl.pos.x);
	printf("Player pos y: %f\n", game->pl.pos.y);
	printf("Player dir x: %f\n", game->pl.dir.x);
	printf("Player dir y: %f\n", game->pl.dir.y);
	printf("Player plane x: %f\n", game->pl.plane.x);
	printf("Player plane y: %f\n", game->pl.plane.y);
	printf("Player pitch: %d\n", game->pl.pitch);
	printf("Player img index: %d\n", game->pl.img_index);
	printf("Player diagonal dist x: %f\n", game->pl.diagonal_dist.x);
	printf("Player diagonal dist y: %f\n", game->pl.diagonal_dist.y);
	printf("Player delta dist x: %f\n", game->pl.delta_dist.x);
	printf("Player delta dist y: %f\n", game->pl.delta_dist.y);
	printf("Player map check x: %d\n", game->pl.map_check.x);
	printf("Player map check y: %d\n", game->pl.map_check.y);
	printf("Player step x: %d\n", game->pl.step.x);
	printf("Player step y: %d\n", game->pl.step.y);
	printf("Player hit dist: %f\n", game->pl.hit_dist);
	printf("Player hit x: %d\n", game->pl.hit_x);
	printf("Player draw start: %d\n", game->pl.draw.start);
	printf("Player draw end: %d\n", game->pl.draw.end);
	printf("Player draw step: %f\n", game->pl.draw.step);
	printf("Player draw pos: %f\n", game->pl.draw.pos);
	printf("Player mouse pos x: %d\n", game->mouse.pos.x);
	printf("Player mouse pos y: %d\n", game->mouse.pos.y);
	printf("Player mouse prev pos x: %d\n", game->mouse.prev_pos.x);
	printf("Player mouse prev pos y: %d\n", game->mouse.prev_pos.y);
	printf("Player key esc: %d\n", game->key.esc);
	printf("Frame time: %f\n", game->time.frame);
	printf("Game anim door i: %f\n", game->anim_door_i);
	printf("Game anim door dir: %d\n", game->anim_door_dir);
	printf("Game anim door x: %d\n", game->anim_door.x);
	printf("Game anim door y: %d\n", game->anim_door.y);
	printf("Game anim door: %c\n", game->pl.map[game->anim_door.y][game->anim_door.x]);
	print_sprites(game);
}

static void	door(t_game *game)
{
	int			x;
	int			y;
	t_player	*pl;

	pl = &game->pl;
	x = (int)(pl->pos.x + pl->dir.x / 2);
	y = (int)(pl->pos.y + pl->dir.y / 2);
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
	else if (keycode == P) //testes
		print_debug(game);
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
