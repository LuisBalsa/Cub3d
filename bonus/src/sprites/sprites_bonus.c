/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:14:10 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/19 14:15:51 by luide-so         ###   ########.fr       */
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
		{
			game->anim_index = 0;
			game->pl.fire = false;
		}
	}
}

static void	set_sprites_distances_and_anim(t_list *sprites, t_vf2d pos)
{
	t_sprite	*sprite;
	t_list		*tmp;

	tmp = sprites;
	while (tmp)
	{
		sprite = tmp->content;
		sprite->dist = (pos.x - sprite->pos.x) * (pos.x - sprite->pos.x) + \
			(pos.y - sprite->pos.y) * (pos.y - sprite->pos.y);
		if (sprite->img_index == INDEX_FIRE_IMAGE)
			sprite->anim_index = sprite->g->anim_index;
		tmp = tmp->next;
	}
}

static void	sort_sprites_by_distance(t_list **sprites)
{
	t_list		*tmp;
	t_sprite	*sprite;
	t_sprite	*sprite2;

	tmp = *sprites;
	while (tmp->next)
	{
		sprite = tmp->content;
		sprite2 = tmp->next->content;
		if (sprite->dist < sprite2->dist)
		{
			tmp->content = sprite2;
			tmp->next->content = sprite;
			tmp = *sprites;
		}
		else
			tmp = tmp->next;
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
	t_list	*tmp;

	if (!game->sprites)
		return ;
	if (ft_strchr("kh", game->map[(int)game->pl.pos.y][(int)game->pl.pos.x]))
		ft_lstiter(game->sprites, &collect_collectibles);
	set_animation(game);
	set_sprites_distances_and_anim(game->sprites, game->pl.pos);
	sort_sprites_by_distance(&game->sprites);
	tmp = game->sprites;
	while (tmp)
	{
		if (((t_sprite *)tmp->content)->visible
			&& ((t_sprite *)tmp->content)->dist > 0.5)
		{
			animate_enemy(game, tmp->content);
			calculate_sprites(tmp->content, game->pl);
			draw_sprites(game, *(t_sprite *)tmp->content, game->pl.pitch);
		}
		tmp = tmp->next;
	}
}
