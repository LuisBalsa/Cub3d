/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:52:37 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/27 03:01:14 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_hit(t_player *pl, int side, t_vi2d check, t_vi2d step)
{
	if (pl->map[check.y][check.x] == '1')
		pl->img_index = side - (side == 1 && step.x < 0)
			- (side == 3 && step.y < 0);
	if (pl->map[check.y][check.x] == '2')
		pl->img_index = INDEX_DOOR_IMAGE;
}
