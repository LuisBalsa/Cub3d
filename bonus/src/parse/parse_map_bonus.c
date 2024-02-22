/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:56:05 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/22 21:27:49 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	print_map(t_game *game) // testes
{
	int	i;

	i = -1;
	while (game->map[++i])
		printf("%s\n", game->map[i]);
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

static char	*load_map(t_game *game, int fd)
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

	tmp_map = load_map(game, fd);
	game->map = ft_split(tmp_map, '\n');
	if (!game->map)
		error_exit(game, "Failed to allocate memory");
	print_map(game); // testes
	free(tmp_map);
}
