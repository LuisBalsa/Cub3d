/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:14:10 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/04 15:18:20 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	set_animation(t_game *game)
{
	if (clock() - game->anim_time > ANIM_DELAY)
	{
		game->anim_time = clock();
		game->anim_index++;
		if (game->anim_index == 3)
			game->anim_index = 0;
	}
}

static void	set_sprites_distances(t_sprite *sprite, t_vf2d pos, int nbr)
{
	int	i;

	i = -1;
	while (++i <= nbr)
	{
		sprite->dist = (pos.x - sprite->pos.x) * \
			(pos.x - sprite->pos.x) + \
			(pos.y - sprite->pos.y) * \
			(pos.y - sprite->pos.y);
		sprite++;
	}
}

static void	sort_sprites_by_distance(t_sprite *sprite, int nbr)
{
	int			i;
	t_sprite	tmp;

	i = -1;
	while (++i < nbr - 1)
	{
		if (sprite[i].dist < sprite[i + 1].dist)
		{
			tmp = sprite[i];
			sprite[i] = sprite[i + 1];
			sprite[i + 1] = tmp;
			i = -1;
		}
	}
}

static void	calculate_sprites(t_sprite *sprite, t_player pl)
{
	t_vf2d	sp;
	double	inv_det;

	sp.x = sprite->pos.x - pl.pos.x;
	sp.y = sprite->pos.y - pl.pos.y;
	inv_det = 1.0 / (pl.plane.x * pl.dir.y - pl.dir.x * pl.plane.y);
	sprite->transform.x = inv_det * (pl.dir.y * sp.x - pl.dir.x * sp.y);
	sprite->transform.y = inv_det * (-pl.plane.y * sp.x + pl.plane.x * sp.y);
	sprite->screen_x = (int)((SCREEN_WIDTH / 2) * \
		(1 + sprite->transform.x / sprite->transform.y));
	sprite->height = abs((int)(SCREEN_HEIGHT / sprite->transform.y));
	sprite->draw_start.y = -sprite->height / 2 + SCREEN_HEIGHT / 2 + pl.pitch;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->height / 2 + SCREEN_HEIGHT / 2 + pl.pitch;
	if (sprite->draw_end.y >= SCREEN_HEIGHT)
		sprite->draw_end.y = SCREEN_HEIGHT - 1;
	sprite->width = abs((int)(SCREEN_HEIGHT / sprite->transform.y));
	sprite->draw_start.x = sprite->screen_x - sprite->width / 2;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->screen_x + sprite->width / 2;
	if (sprite->draw_end.x >= SCREEN_WIDTH)
		sprite->draw_end.x = SCREEN_WIDTH - 1;
}

void	sprites(t_game *game)
{
	int	i;

	set_animation(game);
	set_sprites_distances(game->sprite, game->pl.pos, game->num_sprites);
	sort_sprites_by_distance(game->sprite, game->num_sprites);
	i = -1;
	while (++i <= game->num_sprites)
	{
		calculate_sprites(&game->sprite[i], game->pl);
		draw_sprites(game, game->sprite[i], game->pl.pitch);
	}
}
