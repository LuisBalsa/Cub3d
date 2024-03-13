/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:15:19 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/13 15:11:25 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <time.h>
# include "../../Libft/libft.h"
# include "../../minilibx-linux/mlx.h"

# define GAME_NAME "Cub3D"
# define NBR_PARAMS 6
# define NBR_TEXTURES 14
# define NBR_SPRITES 30

# define VALID_CHARS " 0123NSEWecbtkf\n"
# define SPAWN_CHARS "NSEW"
# define INSIDE_CHARS "023NSEWecbtkf"

# define SPRITE_CHARS "ecbtkf"
# define ENEMY_IMAGE "textures/enemy.xpm"
# define CAGE_IMAGE "textures/cage.xpm"
# define BARREL_IMAGE "textures/barrel.xpm"
# define TABLE_IMAGE "textures/table.xpm"
# define FIRE_IMAGE "textures/fire.xpm"
# define FIRE1_IMAGE "textures/fire1.xpm"
# define FIRE2_IMAGE "textures/fire2.xpm"
# define KEY_IMAGE "textures/key.xpm"
# define INDEX_SPRITE_IMAGE 6

# define DOOR_IMAGE "textures/door.xpm"
# define DOOR_FRAME "textures/door_frame.xpm"
# define INDEX_DOOR_IMAGE 4

# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define OPEN_DOOR '3'
# define OPENING_DOOR '4'
# define CLOSING_DOOR '5'
# define FOV 0.66
# define PITCH 300
# define PITCH_SPD 1000
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 960
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define MV_SPD 3.5
# define R_SPD 2.1
# define R_SPD_M 0.1
# define ANIM_DELAY 100000
# define ANIM_DOOR_DELAY 1000

# define MINIMAP_TILE_S 5
# define MINIMAP_W 43
# define MINIMAP_H 31
# define MINIMAP_OFFSET 1
# define MINIMAP_HITS 600

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

typedef enum e_key
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	E = 101,
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

typedef struct s_mouse
{
	t_vi2d	pos;
	t_vi2d	prev_pos;
}	t_mouse;

typedef struct s_time
{
	double	old;
	double	new;
	double	frame;
}	t_time;

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

typedef struct s_minimap
{
	t_vi2d		map_pos_initial;
	t_vi2d		map_pos_index;
	int			tile_color;
	char		**map;
	char		**map_hit;
}	t_minimap;

typedef struct s_sprite
{
	double	dist;
	t_vf2d	pos;
	t_vf2d	transform;
	int		screen_x;
	int		height;
	int		width;
	t_vi2d	draw_start;
	t_vi2d	draw_end;
	t_vi2d	tex;
	int		img_index;
	bool	anim;
}	t_sprite;

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
	t_sprite	sprite[NBR_SPRITES];
	int			num_sprites;
	t_img		screen;
	double		wall_dist[SCREEN_WIDTH];
	int			color[2];
	char		**map;
	int			map_height;
	t_key_state	key;
	t_mouse		mouse;
	t_player	pl;
	t_time		time;
	double		anim_time;
	int			anim_index;
	double		anim_door_time;
	int			anim_door_i;
	int			anim_door_dir;
	t_vi2d		anim_door;
	t_minimap	minimap;
}	t_game;

int		error_exit(t_game *game, char *message);
int		free_game(t_game *game);

int		parse_file(t_game *game, char *file);
int		lexer(t_game *game, char **tokens);
void	parse_map(t_game *game, int fd);
void	parse_sprites(t_game *game, int x, int y);
void	init_mlx_and_textures(t_game *game);
int		raycasting(t_game *game);
void	perform_dda(t_player *pl);
void	perform_dda_sliding_door(t_player *pl);
void	check_hit(t_player *pl, int *side, t_vi2d check);
void	check_hit_sliding_door(t_player *pl, int *side, t_vi2d check);
void	draw_walls_and_background(t_game *game, t_player *pl, int x);
void	sprites(t_game *game);
void	draw_sprites(t_game *game, t_sprite sprite, int pitch);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	input_handler(t_game *game);
int		mouse_movement_handler(int x, int y, t_game *game);
int		mouse_click_handler(int button, int x, int y, t_game *game);
void	minimap(t_game *game);
void	minimap_raycaster(t_game *game);
void	init_map(char **map);
void	draw_minimap_tile(t_game *game, t_vi2d	pos_index, int color);

#endif
