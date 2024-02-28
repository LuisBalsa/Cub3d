/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:26:53 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/28 11:16:56 by luide-so         ###   ########.fr       */
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

static void	print_debug(t_game *game)
{
	printf("Player pos x: %f\n", game->pl.pos.x);
	printf("Player pos y: %f\n", game->pl.pos.y);
	printf("Player dir x: %f\n", game->pl.dir.x);
	printf("Player dir y: %f\n", game->pl.dir.y);
	printf("Player plane x: %f\n", game->pl.plane.x);
	printf("Player plane y: %f\n", game->pl.plane.y);
	printf("Player pitch: %d\n", game->pl.pitch);
	printf("Player img index: %d\n", game->pl.img_index);
	printf("Player diagonal dist x: %f\n", game->pl.diagonal_dist.x);
	printf("Player diagonal dist y: %f\n", game->pl.diagonal_dist.y);
	printf("Player delta dist x: %f\n", game->pl.delta_dist.x);
	printf("Player delta dist y: %f\n", game->pl.delta_dist.y);
	printf("Player map check x: %d\n", game->pl.map_check.x);
	printf("Player map check y: %d\n", game->pl.map_check.y);
	printf("Player step x: %d\n", game->pl.step.x);
	printf("Player step y: %d\n", game->pl.step.y);
	printf("Player hit dist: %f\n", game->pl.hit_dist);
	printf("Player hit x: %d\n", game->pl.hit_x);
	printf("Player draw start: %d\n", game->pl.draw.start);
	printf("Player draw end: %d\n", game->pl.draw.end);
	printf("Player draw step: %f\n", game->pl.draw.step);
	printf("Player draw pos: %f\n", game->pl.draw.pos);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->key.w = 0;
	if (keycode == A)
		game->key.a = 0;
	if (keycode == S)
		game->key.s = 0;
	if (keycode == D)
		game->key.d = 0;
	if (keycode == LEFT)
		game->key.left = 0;
	if (keycode == RIGHT)
		game->key.right = 0;
	if (keycode == P)
		print_debug(game);
	return (0);
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
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
