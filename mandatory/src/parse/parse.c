/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:27:11 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/17 23:48:27 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	print_tokens(char **tokens) // testes
{
	int	i;

	i = 0;
	while (*tokens && tokens[i])
	{
		printf("%d %s\n", i, tokens[i]);
		i++;
	}
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

static void	lexer(t_game *game, int fd) // passar para parse_file
{
	char	*line;
	char	*tokens[5];
//	int		valid_params;

//	valid_params = 0;
	line = get_next_line(fd);
	while (line)
	{
		tokenizer(game, line, tokens);
		if (*tokens && ft_isdigit(tokens[0][0]))
			break ;
		print_tokens(tokens); // valid_params = parse_params(game, tokens);
		free(line);
		line = get_next_line(fd);
	}
	//	if (valid_params != NBR_PARAMS)
	//		return (error_exit(game, "Parameters missing"));
//===>> dentro do parse map
	if (!line)
		return (error_exit(game, "No map found"), (void)(0));
	printf("\nmap\n\n %s\n", line);
	free(line);
//<<===
}

static int	check_open_file(t_game *game, char *file)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + len - 4, ".cub", 4) || len < 5)
		return (error_exit(game, "Invalid file extension"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_exit(game, "Failed to open file"));
	return (fd);
}

int	parse_file(t_game *game, char *file)
{
	int		fd;

	fd = check_open_file(game, file);
	lexer(game, fd);
	close(fd);
	return (0);
}
