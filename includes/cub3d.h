/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoeller <tmoeller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:03:40 by shmoreno          #+#    #+#             */
/*   Updated: 2024/12/16 14:46:39 by tmoeller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/includes/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WINDOW_TITLE "cub3d"
# define WIN_WIDTH 2200
# define WIN_HEIGHT 1080
# define MID_X (WIN_WIDTH / 2)			// AJOUTEZ CETTE LIGNE APRES WIN_WIDTH
# define MID_Y (WIN_HEIGHT / 2)			// AJOUTEZ CETTE LIGNE APRES WIN HEIGHT
# define MAX_QUEUE_SIZE 1000
# define NUM_XPM_FILES 49
# define PLY_POV 60
# define PLY_ROTATE 0.04
# define PLY_WALK 4
# define M_PI 3.14159265358979323846

#define NORTH_WALL_TEXTURE	0xFFFFFF // White
#define SOUTH_WALL_TEXTURE	0xFF0000 // Red
#define EAST_WALL_TEXTURE	0x00FF00 // Green
#define WEST_WALL_TEXTURE	0x0000FF // Blue
#define CEILING_COLOR		0x87CEEB // Sky blue
#define FLOOR_COLOR			0x8B4513 // Brown

/*
KEY_LEFT: 97 == "A" key on the keyboard.
KEY_RIGHT: 100 == "D" key on the keyboard.
KEY_UP: 119 == "W" key on the keyboard.
KEY_DOWN: 115 == "S" key on the keyboard.
KEY_ACTION: 101 == "E" key on the keyboard.
KEY_ARROW_LEFT: 65361 == left arrow key.
KEY_ARROW_RIGHT: 65363 == right arrow key.
KEY_ARROW_UP: 65362 == up arrow key.
KEY_ARROW_DOWN: 65364 == down arrow key.
KEY_SPACE_BAR: 32 == space bar on the keyboard.
KEY_ESC: 65307 == "ESC" (escape) key on the keyboard.
*/
# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
#  define OS "linux"
//#  define KEY_LEFT		97
//#  define KEY_RIGHT		100
//#  define KEY_UP       	119
//#  define KEY_DOWN		115
#  define KEY_W			119
#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_ARROW_LEFT	 	65361
#  define KEY_ARROW_RIGHT		65363
#  define KEY_ARROW_UP			65362
#  define KEY_ARROW_DOWN		65364
#  define KEY_ESC				65307
# elif __APPLE__
#  include "../minilibx_opengl_20191021/mlx.h"
#  define OS "macos"
#  define KEY_LEFT       0
#  define KEY_RIGHT      2
#  define KEY_UP 		13
#  define KEY_DOWN		1
#  define KEY_ARROW_LEFT		123
#  define KEY_ARROW_RIGHT		124
#  define KEY_ARROW_UP			126
#  define KEY_ARROW_DOWN		125
#  define KEY_ESC				53
# endif

// DEBUG MACROS
# define PL fprintf(stderr, "file: %s line: %d pid: %i\n", \
	__FILE__, __LINE__, getpid())
/*# define PI(x) fprintf(stderr, "PI: %d\n", (x));
# define PS(x) fprintf(stderr, "PS: %s\n", (x));
# define PI2(s, x) fprintf(stderr, "%s: %d\n", (s), (x));
# define PS2(s, x) fprintf(stderr, "%s: %s\n", (s), (x));
*/

typedef struct s_ply
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x; // Vecteur de plan de camera X
	double	plane_y; // Vecteur de plan de camera Y
	double	frame_time;
	double	move_speed;
	double	rotate_speed;
	double	time;
	double	old_time;
	double	sensitivity;			// AJOUTEZ CETTE LIGNE

	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	right;
	bool	left;

	float	dir_angle;
	float	pov_rad;
	float	angle;
}	t_ply;

typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		side;
	int		x;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
}	t_ray;

typedef struct s_map
{
	char	**map;
	char	**directions;
	char	*line;
}	t_map;

typedef struct s_img
{
	int		height;
	int		width;
	void	*i;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_game
{
	void		*p_mlx_init;
	void		*p_mlx_window;
	void		*ptr_to_image;
	t_img		img;
	t_ray		*ray;
	t_map		*map;
	t_ply		*ply;
	t_tex		tex[4];
}	t_game;



// FUNCTION CUB3D /-\ srcs/cub3d.c
void	ft_init_main(t_game *game, char *argv);

// FUNCTION ERROR /-\ srcs/error/error.c
void	ft_error(char *str, int count);
void	ft_error_dir(t_map *map, char c, int i);
void	ft_error_rgb(void);

// FUNCTION GAME SETTINGS /-\ srcs/game/settings.c
int		ft_destroy_escape(int keysim, t_game *game);
int		ft_destroy_cross(t_game *game);
int		ft_resize_window(t_map *map);

// FUNCTION PARSING /-\ srcs/parsing/parsing.c
int		ft_parse_base(t_game *game, int argc, char **argv);
void	ft_check_rgb_color(t_map *map, int i, int *c_rgb, int *c_separate);

// FUNCTION PARSING /-\ srcs/parsing/parsing_map.c
void	ft_map_route(t_game *game, int count);

// FUNCTION PARSING /-\ srcs/parsing/verify_direction.c
void	ft_init_dir(t_map *map, char *line, int *count, bool *out_direction);

// FUNCTION PARSING /-\ srcs/parsing/verify_map.c
void	ft_verify_map(t_game *game, int count);

// FUNCTION RAYCASTING /-\ srcs/raycasting/raycasting_init.c
void	ft_init_raycast(t_game *game);
void	ft_init(t_game *game);
void	ft_dda_algo(t_game *game);

// FUNCTION RAYCASTING /-\ srcs/raycasting/raycasting_calcul.c
void	perp_init(t_game *game);
void	process_dda(t_game *game);
void	calculate_line_height(t_game *game);
void	update_frame_time(t_game *game);

// FUNCTION RAYCASTING /-\ srcs/raycasting/raycasting_draw.c
void	cast_rays(t_game *game);
void	choose_wall_texture(t_game *game);
void	draw_vertical_line(t_game *game);

// FUNCTION TEXTURE /-\ srvs/texturing/init_textures.c
void	ft_init_textures(t_game *game);
int		get_tex_color(t_tex *t, int x, int y);
int		choose_tex_id(t_game *game);
void	draw_textured_line(t_game *game, int tex_id);

// FUNCTION TEXTURE /-\ srvs/texturing/draw_textures.c
void	draw_textured_line(t_game *g, int tex_id);

// FUNCTION PLAYER /-\ srcs/player/intit_player_controls.c
int 	ft_update_game(void *param);
void	init_player(t_game *game);

// FUNCTION PLAYER /-\ srcs/player/player_movement.c
void	move_forward(t_game *game);
void	move_backwards(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

// FUNCTION PLAYER /-\ srcs/player/rotate.c
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	rotate_player(t_game *game, double angle);
int		mouse_move(int x, int y, void *param);

// FUNCTION PLAYER /-\ srcs/player/keys.c
int	key_release(int keycode, void *param);
int	key_press(int keycode, void *param);

// FUNCTION UTILS /-\ srcs/utils/function_utils.c
int		ft_strlen_find(char *str, char c);
int		ft_count_index(char **input);
double	get_time(void);

// FUNCTION UTILS MLX /-\ srcs/utils-mlx/function_mlx.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

// FUNCTION UTILS /-\ srcs/utils/parsing_utils.c
bool	ft_only_espace(const char *line);
bool	ft_only_iswall(const char *line);
int		ft_malloc_size(char *argv);
int		ft_check_dir(t_map *map);

#endif