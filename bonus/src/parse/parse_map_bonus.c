/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:56:05 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/27 14:40:42 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	set_spawn(t_game *ga, char dir, int x, int y)
{
	t_player	*pl;

	if (ga->pl.g)
		error_exit(ga, "Map has multiple spawn points");
	pl = &ga->pl;
	pl->pos = (t_vf2d){x + 0.5, y + 0.5};
	pl->dir = (t_vf2d){(dir == 'E') - (dir == 'W'),
		(dir == 'S') - (dir == 'N')};
	pl->plane = (t_vf2d){(pl->dir.y * FOV) * -1, pl->dir.x * FOV};
	ga->map[y][x] = FLOOR;
	pl->g = ga;
	pl->map = ga->map;
}

static void	validate_map_and_set_spawn(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr(INSIDE_CHARS, game->map[y][x]))
				if (x == 0 || y == 0 || !game->map[y + 1]
					|| !game->map[y][x + 1]
					|| x >= (int)ft_strlen(game->map[y - 1])
					|| x >= (int)ft_strlen(game->map[y + 1])
					|| game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' '
					|| game->map[y - 1][x] == ' ' || game->map[y + 1][x] == ' ')
					error_exit(game, "Map is not closed");
			if (ft_strchr(SPAWN_CHARS, game->map[y][x]))
				set_spawn(game, game->map[y][x], x, y);
			if (game->map[y][x] == DOOR &&
				(game->map[y][x - 1] != WALL || game->map[y][x + 1] != WALL) &&
				(game->map[y - 1][x] != WALL || game->map[y + 1][x] != WALL))
				error_exit(game, "Map has invalid door");
		}
	}
}

static int	line_has_valid_content(t_game *game, char *line)
{
	int	i;

	i = -1;
	while (game->file_line && ft_strchr(" \t", game->file_line[++i]))
		;
	if (!game->file_line || !game->file_line[i] || game->file_line[i] == '\n')
		return (false);
	i = -1;
	while (game->file_line[++i])
	{
		if (!ft_strchr(VALID_CHARS, game->file_line[i]))
		{
			if (line)
				free(line);
			return (error_exit(game, "Map has invalid characters"), false);
		}
	}
	return (true);
}

static char	*load_map_and_check_content(t_game *game, int fd)
{
	char	*tmp_map;
	char	*old_temp_map;

	tmp_map = NULL;
	while (line_has_valid_content(game, tmp_map))
	{
		old_temp_map = tmp_map;
		tmp_map = ft_strjoin(tmp_map, game->file_line);
		if (old_temp_map)
			free(old_temp_map);
		if (!tmp_map)
			return (error_exit(game, "Failed to allocate memory"), NULL);
		free(game->file_line);
		game->file_line = get_next_line(fd);
	}
	while (game->file_line)
	{
		free(game->file_line);
		game->file_line = get_next_line(fd);
		if (line_has_valid_content(game, tmp_map))
			return (free(tmp_map),
				error_exit(game, "Map has empty lines"), NULL);
	}
	return (tmp_map);
}

void	parse_map(t_game *game, int fd)
{
	char	*tmp_map;

	tmp_map = load_map_and_check_content(game, fd);
	game->map = ft_split(tmp_map, '\n');
	free(tmp_map);
	if (!game->map)
		error_exit(game, "Failed to allocate memory");
	validate_map_and_set_spawn(game);
}
