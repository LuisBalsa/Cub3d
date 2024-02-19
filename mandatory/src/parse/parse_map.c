/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:56:05 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/18 18:26:52 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*load_map(t_game *game, int fd, char *line)
{
	while (line_not_empty(line))
	{
		add_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line_not_empty(line))
			return (error_exit(game, "Map can't have empty lines"));
	}
	

void	parse_map(t_game *game, int fd, char *line)
{
	char	*tmp;

	tmp = load_map(game, fd, line);
}

