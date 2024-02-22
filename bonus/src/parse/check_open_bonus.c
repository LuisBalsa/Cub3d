/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:46:49 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/22 19:51:42 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	check_open(t_game *game, char *file, char *extension)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + len - 4, extension, 4) || len < 5)
		return (error_exit(game, "Invalid file/texture extension"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_exit(game, "Failed to open file/texture"));
	return (fd);
}
