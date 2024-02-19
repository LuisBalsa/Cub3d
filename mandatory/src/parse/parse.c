/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:27:11 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/19 22:39:50 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	print_params_and_colors(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		printf("Texture %d: %s\n", i, game->texture[i]);
	printf("Ceiling color: %d\n", game->color[clg]);
	printf("Floor color: %d\n", game->color[flr]);
}

static int	assign_texture(t_game *game, t_texture texture, char **tokens)
{
	if (game->texture[texture])
		return (error_exit(game, "Texture duplicated"));
	if (!tokens[1] || tokens[2])
		return (error_exit(game, "Invalid texture path"));
	close(check_open(game, tokens[1], ".xpm"));
	game->texture[texture] = ft_strdup(tokens[1]);
	if (!game->texture[texture])
		return (error_exit(game, "Failed to assign texture"));
	return (true);
}

static int	assign_color(t_game *game, t_color color, char **tokens)
{
	int	i;
	int	j;
	int	rgb[3];

	if (game->color[color])
		return (error_exit(game, "Color duplicated"));
	i = 0;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
			if (!ft_isdigit(tokens[i][j]))
				return (error_exit(game, "Color must be a number"));
	}
	if (i != 4)
		return (error_exit(game, "RGB color must have 3 values"));
	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(tokens[i + 1]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (error_exit(game, "Invalid color range"));
	}
	game->color[color] = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (true);
}

static int	lexer(t_game *game, char *line, char **tokens)
{
	free(line);
	if (!ft_strncmp(tokens[0], "NO", 3))
		return (assign_texture(game, no, tokens));
	if (!ft_strncmp(tokens[0], "SO", 3))
		return (assign_texture(game, so, tokens));
	if (!ft_strncmp(tokens[0], "WE", 3))
		return (assign_texture(game, we, tokens));
	if (!ft_strncmp(tokens[0], "EA", 3))
		return (assign_texture(game, ea, tokens));
	if (!ft_strncmp(tokens[0], "C", 2))
		return (assign_color(game, clg, tokens));
	if (!ft_strncmp(tokens[0], "F", 2))
		return (assign_color(game, flr, tokens));
	return (error_exit(game, "Invalid parameter"));
}

static void	tokenizer(t_game *ga, char *line, char **tokens)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && ft_strchr(" \t\n", line[i]))
		i++;
	if (!line[i])
		return (tokens[0] = NULL, (void)(0));
	while (line[i])
	{
		tokens[j++] = line + i;
		while (line[i] && !ft_strchr(" \t\n,", line[i]))
			i++;
		if (line[i])
			line[i++] = '\0';
		while (line[i] && ft_strchr(" \t\n", line[i]))
			i++;
		if (j > 4)
			return (free(line), error_exit(ga, "Invalid parameter"), (void)(0));
	}
	tokens[j] = NULL;
}

int	parse_file(t_game *game, char *file)
{
	int		fd;
	char	*line;
	char	*tokens[5];
	int		valid_params;

	fd = check_open(game, file, ".cub");
	valid_params = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (error_exit(game, "No map found"));
		tokenizer(game, line, tokens);
		if (*tokens && ft_isdigit(tokens[0][0]))
			break ;
		if (*tokens)
			valid_params += lexer(game, line, tokens);
		else
			free(line);
	}
	if (valid_params != NBR_PARAMS)
		return (error_exit(game, "Parameters missing"));
//	parse_map(game, fd, line);
	free(line); // inside parse_map
	print_params_and_colors(game);
	close(fd);
	return (0);
}
