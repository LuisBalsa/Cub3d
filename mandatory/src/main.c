/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:26:53 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/17 12:08:15 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game(t_game *game)
{
	if (!game)
		return ;
}

int	error_exit(t_game *game, char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	free_game(game);
	exit(errno);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){0};
	errno = 1;
	if (argc != 2)
		return (error_exit(NULL, "Invalid number of arguments"));
	parse_file(&game, argv[1]);
	return (0);
}
