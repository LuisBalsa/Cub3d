/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collectables_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:02:51 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/13 20:54:25 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	reload_sprites(t_game *game)
{
	int	y;
	int	x;

	game->num_sprites = 0;
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr(SPRITE_CHARS, game->map[y][x]))
				parse_sprites(game, x, y);
		}
	}
}

void	check_collectables(t_game *game)
{
	char	*collectibles;

	if (game->map[(int)game->pl.pos.y][(int)game->pl.pos.x] == 'k')
	{
		game->map[(int)game->pl.pos.y][(int)game->pl.pos.x] = '0';
		game->nbr_collectibles--;
		reload_sprites(game);
	}
	if (game->nbr_collectibles == 0)
	{
		mlx_string_put(game->mlx, game->win, MINIMAP_W + 200, 50, 0x000000,
			"Congratulations! You collected all the keys!");
	}
	else
	{
		mlx_string_put(game->mlx, game->win, MINIMAP_W + 200, 50, 0x000000,
			"Collect the remaining keys:");
		mlx_string_put(game->mlx, game->win, MINIMAP_W + 400, 50, 0x000000,
			collectibles = ft_itoa(game->nbr_collectibles));
		free(collectibles);
	}
}
