/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:15:19 by luide-so          #+#    #+#             */
/*   Updated: 2024/03/17 22:50:11 by luide-so         ###   ########.fr       */
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
# define NBR_PARAMS 7
# define NBR_TEXTURES 33

# define VALID_CHARS " 01236789NSEWecbtkf\n"
# define SPAWN_CHARS "NSEW"
# define INSIDE_CHARS "023NSEWecbtkf"
# define SPRITE_CHARS "cbtkfe"

# define DOOR_IMAGE "door.xpm"
# define DOOR_FRAME "door_frame.xpm"
# define ENEMY_IMAGE "enemy.xpm"
# define ENEMY1_IMAGE "enemy1.xpm"
# define ENEMY2_IMAGE "enemy2.xpm"
# define ENEMY3_IMAGE "enemy3.xpm"
# define ENEMY4_IMAGE "enemy4.xpm"
# define ENEMY5_IMAGE "enemy5.xpm"
# define ENEMY6_IMAGE "enemy6.xpm"
# define ENEMY7_IMAGE "enemy7.xpm"
# define ENEMY8_IMAGE "enemy8.xpm"
# define ENEMY9_IMAGE "enemy9.xpm"
# define ENEMY10_IMAGE "enemy10.xpm"
# define ENEMY11_IMAGE "enemy11.xpm"
# define ENEMY12_IMAGE "enemy12.xpm"
# define ENEMY13_IMAGE "enemy13.xpm"
# define ENEMY14_IMAGE "enemy14.xpm"
# define CAGE_IMAGE "cage.xpm"
# define BARREL_IMAGE "barrel.xpm"
# define TABLE_IMAGE "table.xpm"
# define KEY_IMAGE "key.xpm"
# define FIRE_IMAGE "fire.xpm"
# define FIRE1_IMAGE "fire1.xpm"
# define FIRE2_IMAGE "fire2.xpm"
# define WALL1_IMAGE "wall1.xpm"
# define WALL2_IMAGE "wall2.xpm"
# define WALL3_IMAGE "wall3.xpm"
# define WALL4_IMAGE "wall4.xpm"
# define HIT_IMAGE "hit.xpm"
# define INDEX_DOOR_IMAGE 4
# define INDEX_SPRITE_IMAGE 6
# define INDEX_FIRE_IMAGE 10
# define INDEX_WALL_IMAGE 13
# define INDEX_ENEMY_IMAGE 17
# define INDEX_HIT_IMAGE 32
# define I_W_ASCII_DIFF 41

# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define OPEN_DOOR '3'
# define OPENING_DOOR '4'
# define CLOSING_DOOR '5'
# define WALKABLE "03k"
# define TRANSPOSABLE "023ek"
# define FOV 0.66
# define PITCH 300
# define PITCH_SPD 1000
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 960
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define MV_SPD 3.5
# define R_SPD 3.1
# define R_SPD_M 0.1
# define ANIM_DELAY 100000
# define ANIM_DOOR_DELAY 1000
# define DOOR_SPD 200
# define HIT_BLUR_SPD 1

# define MINIMAP_TILE_S 5
# define MINIMAP_W 43
# define MINIMAP_H 31
# define MINIMAP_OFFSET 1
# define MINIMAP_HITS 600

# define ENEMY_SHOOTING 0
# define ENEMY_WALKING 5
# define ENEMY_DYING 10

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
	SPACEBAR = 32,
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

typedef struct s_enemy
{
	t_vf2d		hited;
}	t_enemy;

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
	int		anim_index;
	double	anim_time;
	bool	visible;
	bool	enemy_animated;
	int		mode;
	t_game	*g;
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
	int			hits_taken;
	double		hited;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*file_line;
	char		*texture[NBR_TEXTURES];
	char		*theme_directory;
	t_img		img[NBR_TEXTURES];
	t_list		*sprites;
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
	double		anim_door_i;
	int			anim_door_dir;
	t_vi2d		anim_door;
	t_minimap	minimap;
	int			nbr_collectibles;
	bool		collectibles_found;
	t_enemy		enemy;
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
int		my_pixel_get(t_img *mlx, int x, int y);
void	my_pixel_put(t_img *mlx, int x, int y, int color);
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
void	sprites_collectable_count(char **map, int *count, int x, int y);

void	check_shot(t_game *game);
void	set_enemy_as_animated(void *sprite);
void	animate_enemy(t_game *game, t_sprite *sprite);

void	draw_hit_blur(t_img *img, t_img *screen);

#endif
