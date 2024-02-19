/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:15:19 by luide-so          #+#    #+#             */
/*   Updated: 2024/02/19 23:16:28 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "../../Libft/libft.h"
# include "../../minilibx-linux/mlx.h"

# define NBR_PARAMS 6
# define NBR_TEXTURES 4
# define PI 3.14159265358979323846
# define TWO_PI 6.28318530717958647692

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

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_fl_point
{
	double	x;
	double	y;
}	t_fl_point;

typedef struct s_player
{
	t_fl_point	pos;
	t_fl_point	dir;
	t_fl_point	plane;
}	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	*file_line;
	char	*texture[4];
	int		color[2];
	char	**map;
}	t_game;

int		error_exit(t_game *game, char *message);
void	free_game(t_game *game);
int		check_open(t_game *game, char *file, char *extension);

int		parse_file(t_game *game, char *file);
void	parse_map(t_game *game, int fd, char *line);

#endif
