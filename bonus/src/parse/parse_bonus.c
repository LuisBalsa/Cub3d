/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:27:11 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/23 15:59:48 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	check_open(t_game *game, char *file, char *extension)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + len - 4, extension, 4) || len < 5)
		return (error_exit(game, "Invalid file extension"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_exit(game, "Failed to open file"));
	return (fd);
}

static void	print_params_and_colors(t_game *game) // testes
{
	int	i;

	i = -1;
	while (++i < 4)
		printf("Texture %d: %s\n", i, game->texture[i]);
	printf("Ceiling color: %d\n", game->color[clg]);
	printf("Floor color: %d\n", game->color[flr]);
}


static void	tokenizer(t_game *ga, char **tokens)
{
	int		i;
	int		j;
	int		comma;

	i = 0;
	j = 0;
	comma = 0;
	while (ga->file_line[i] && ft_strchr(" \t\n", ga->file_line[i]))
		i++;
	while (ga->file_line[i])
	{
		tokens[j++] = ga->file_line + i;
		if (j == 1 && ft_isdigit(ga->file_line[i]))
			break ;
		while (ga->file_line[i] && !ft_strchr(" \t\n,", ga->file_line[i]))
			i++;
		comma += (ga->file_line[i] == ',') * (j != 1) * j;
		if (ga->file_line[i])
			ga->file_line[i++] = '\0';
		while (ga->file_line[i] && ft_strchr(" \t\n,", ga->file_line[i]))
			comma += (ga->file_line[i++] == ',') * (j != 1) * j;
		if (j > 4 || (j == 4 && ft_strchr("CF", tokens[0][0]) && comma != 5))
			return (error_exit(ga, "Invalid parameter"), (void)(0));
	}
	tokens[j] = NULL;
}

int	parse_file(t_game *game, char *file)
{
	int		fd;
	char	*tokens[5];
	int		valid_params;

	fd = check_open(game, file, ".cub");
	valid_params = 0;
	while (1)
	{
		game->file_line = get_next_line(fd);
		if (!game->file_line)
			return (error_exit(game, "No map found"));
		tokenizer(game, tokens);
		if (*tokens && ft_isdigit(tokens[0][0]))
			break ;
		if (*tokens)
			valid_params += lexer(game, tokens);
		free(game->file_line);
	}
	if (valid_params != NBR_PARAMS)
		return (error_exit(game, "Parameters missing"));
	print_params_and_colors(game); // testes
	parse_map(game, fd);
	close(fd);
	return (0);
}
