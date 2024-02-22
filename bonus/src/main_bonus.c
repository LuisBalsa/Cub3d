/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:26:53 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/22 19:20:12 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	if (game->file_line)
		free(game->file_line);
	i = -1;
	while (++i < 4)
		if (game->texture[i])
			free(game->texture[i]);
}

int	error_exit(t_game *game, char *message)
{
	ft_putendl_fd(RED"Error", 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(RESET, 2);
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
	free_game(&game);
	return (0);
}
