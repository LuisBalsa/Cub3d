/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:15:19 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/23 10:09:12 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "../../Libft/libft.h"
# include "../../minilibx-linux/mlx.h"

# define NBR_PARAMS 6
# define NBR_TEXTURES 4
# define VALID_CHARS " 012NSEW\n"
# define SPAWN_CHARS "NSEW"
# define INSIDE_CHARS "02NSEW"
# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define PI 3.14159265358979323846
# define TWO_PI 6.28318530717958647692

typedef struct s_game	t_game;

typedef enum e_texture
{
	no,
	so,
	we,
	ea
}	t_texture;

typedef enum e_color
{
	clg,
	flr
}	t_color;

typedef struct s_vi2d
{
	int	x;
	int	y;
}	t_vi2d;

typedef struct s_vf2d
{
	double	x;
	double	y;
}	t_vf2d;

typedef struct s_player
{
	t_game	*g;
	char	**map;
	t_vf2d	pos;
	t_vf2d	ray_dir;
	t_vf2d	camera;
	t_vf2d	side_len;
	t_vf2d	ray_len;
	t_vi2d	map_check;
	t_vi2d	step;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*file_line;
	char		*texture[NBR_TEXTURES];
	int			color[2];
	char		**map;
	t_player	pl;
}	t_game;

int		error_exit(t_game *game, char *message);
void	free_game(t_game *game);
int		check_open(t_game *game, char *file, char *extension);

int		parse_file(t_game *game, char *file);
void	parse_map(t_game *game, int fd);

#endif
