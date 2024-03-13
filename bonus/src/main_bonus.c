/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:26:53 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/13 01:44:31 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	free_game_mlx(t_game *game)
{
	int	i;

	i = -1;
	while (++i < NBR_TEXTURES)
		if (game->img[i].img)
			mlx_destroy_image(game->mlx, game->img[i].img);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	free_game(t_game *game)
{
	int	i;

	if (!game)
		return (0);
	if (game->mlx)
		free_game_mlx(game);
	if (game->file_line)
		free(game->file_line);
	i = -1;
	while (++i < NBR_TEXTURES)
		if (game->texture[i])
			free(game->texture[i]);
	if (game->map)
		ft_free_array(game->map);
	if (game->minimap.map)
		ft_free_array(game->minimap.map);
	exit(0);
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
	init_mlx_and_textures(&game);
	raycasting(&game);
	mlx_hook(game.win, 2, 1L << 0, &key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, &key_release, &game);
	mlx_hook(game.win, 17, 1L << 0, &free_game, &game);
	mlx_hook(game.win, 6, 1L << 6, &mouse_movement_handler, &game);
	mlx_hook(game.win, 4, 1L << 2, &mouse_click_handler, &game);
	mlx_loop_hook(game.mlx, &raycasting, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
