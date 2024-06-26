/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:15:19 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/16 23:03:39 by luide-so         ###   ########.fr       */
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

# define GAME_NAME "Cub3D"
# define NBR_PARAMS 6
# define NBR_TEXTURES 4
# define VALID_CHARS " 01NSEW\n"
# define SPAWN_CHARS "NSEW"
# define INSIDE_CHARS "0NSEW"
# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define FOV 0.66
# define PITCH 200
# define PITCH_SPD 5
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define MV_SPD 0.01
# define COS 0.99995000041
# define SIN 0.00999983333

# define DOOR_IMAGE "textures/door.xpm"
# define DOOR_FRAME "textures/door_frame.xpm"
# define INDEX_DOOR_IMAGE 4

typedef struct s_game	t_game;

typedef enum e_texture
{
	we,
	ea,
	no,
	so
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

typedef enum e_key
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	P = 112,
	ESC = 65307,
	UP = 65362,
	LEFT = 65361,
	DOWN = 65364,
	RIGHT = 65363,
}				t_key;

typedef struct s_key_state
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	esc;
	int	up;
	int	left;
	int	down;
	int	right;
}	t_key_state;

typedef struct s_vf2d
{
	double	x;
	double	y;
}	t_vf2d;

typedef struct s_draw
{
	int		start;
	int		end;
	double	step;
	double	pos;
}	t_draw;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	t_game		*g;
	char		**map;
	t_vf2d		pos;
	t_vf2d		dir;
	t_vf2d		ray_dir;
	t_vf2d		plane;
	int			pitch;
	int			img_index;
	t_vf2d		diagonal_dist;
	t_vf2d		delta_dist;
	t_vi2d		map_check;
	t_vi2d		step;
	double		hit_dist;
	int			hit_x;
	t_draw		draw;
	t_key_state	key;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*file_line;
	char		*texture[NBR_TEXTURES];
	t_img		img[NBR_TEXTURES];
	t_img		screen;
	int			color[2];
	char		**map;
	int			map_height;
	t_key_state	key;
	t_player	pl;
}	t_game;

int		error_exit(t_game *game, char *message);
int		free_game(t_game *game);

int		parse_file(t_game *game, char *file);
int		lexer(t_game *game, char **tokens);
void	parse_map(t_game *game, int fd);
void	init_mlx_and_textures(t_game *game);
int		raycasting(t_game *game);
void	check_hit(t_player *pl, int *side, t_vi2d check, t_vi2d step);
void	draw_walls_and_background(t_game *game, t_player *pl, int x);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	input_handler(t_game *game);

#endif
