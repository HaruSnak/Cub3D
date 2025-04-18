/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:03:40 by shmoreno          #+#    #+#             */
/*   Updated: 2025/03/11 20:44:53 by shmoreno         ###   ########.fr       */
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
# define MAX_QUEUE_SIZE 1000
# define COLLISION_BUFFER 0.2
# define NUM_XPM_FILES 49
# define PLY_POV 60
# define PLY_ROTATE 0.04
# define PLY_WALK 4
# define M_PI 3.14159265358979323846
# define TILES_SIZE 10
# define PLAYER_SIZE 6
# define MINIMAP_FLOOR	0x535065
# define MINIMAP_PLAYER	0xADE917
# define MINIMAP_WALL	0xB4AFA7

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
#  define KEY_W			119
#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_ARROW_LEFT	 	65361
#  define KEY_ARROW_RIGHT		65363
#  define KEY_ARROW_UP			65362
#  define KEY_ARROW_DOWN		65364
#  define KEY_ESC				65307
#  define KEY_SPACE				32
# elif __APPLE__
#  include "../minilibx_opengl_20191021/mlx.h"
#  define OS "macos"
#  define KEY_LEFT       0
#  define KEY_RIGHT      2
#  define KEY_UP		13
#  define KEY_DOWN		1
#  define KEY_ARROW_LEFT		123
#  define KEY_ARROW_RIGHT		124
#  define KEY_ARROW_UP			126
#  define KEY_ARROW_DOWN		125
#  define KEY_ESC				53
#  define KEY_SPACE				49
# endif

// DEBUG MACROS
/*# define PL fprintf(stderr, "file: %s line: %d pid: %i\n", \
	__FILE__, __LINE__, getpid())
# define PI(x) fprintf(stderr, "PI: %d\n", (x));
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
	double	plane_x;
	double	plane_y;
	double	frame_time;
	double	move_speed;
	double	rotate_speed;
	double	time;
	double	old_time;
	double	sensitivity;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	right;
	bool	left;
	float	dir_angle;
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
	char	**dir;
	char	*tmp;
	char	*line;
	int		floor_color;
	int		ceiling_color;
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

typedef struct s_texture
{
	void	*i;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
}	t_textures;

typedef struct s_game
{
	void		*img_menu;
	int			mid_x;
	int			mid_y;
	bool		b_menu;
	int			index_map;
	void		*p_mlx_init;
	void		*p_mlx_window;
	void		*ptr_to_image;
	t_img		img;
	t_ray		*ray;
	t_map		*map;
	t_ply		*ply;
	t_textures	textures;
}	t_game;

typedef struct s_move
{
	double	next_x;
	double	next_y;
	int		map_height;
	int		check_x;
	int		check_y;
	int		row_length;
}	t_move;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

# ifdef BONUS
#  define BONUS_VALUE 1
# else
#  define BONUS_VALUE 0
# endif

// FUNCTION CUB3D /-\ srcs/cub3d.c
void			ft_init_main(t_game *game, char *argv);

// FUNCTION ERROR /-\ srcs/error/error.c
void			ft_error(t_game *game, char *str, int count);
void			ft_error_dir(t_game *game, char c, int i);
void			ft_error_rgb(t_game *game);

// FUNCTION GAME SETTINGS /-\ srcs/game/settings.c
int				ft_destroy_cross(t_game *game);

// FUNCTION PARSING /-\ srcs/parsing/parsing.c
int				ft_parse_base(t_game *game, int argc, char **argv);
int				ft_rgb_to_hex(int red, int green, int blue);
void			ft_find_rgb(t_game *game, int index, int i, int count_rgb);

// FUNCTION PARSING /-\ srcs/parsing/parsing_map.c
void			ft_map_route(t_game *game, int count);

// FUNCTION PARSING /-\ srcs/parsing/verify_direction.c
void			ft_init_dir(t_game *game, char *line,
					int *count, bool *out_direction);

// FUNCTION PARSING /-\ srcs/parsing/verify_map.c
void			ft_verify_map(t_game *game, int count);

// FUNCTION RAYCASTING /-\ srcs/raycasting/raycasting_init.c
void			ft_init_raycast(t_game *game);
void			ft_init(t_game *game);
void			ft_dda_algo(t_game *game);

// FUNCTION RAYCASTING /-\ srcs/raycasting/raycasting_calcul.c
void			perp_init(t_game *game);
void			process_dda(t_game *game);
void			calculate_line_height(t_game *game);
void			update_frame_time(t_game *game);

// FUNCTION RAYCASTING /-\ srcs/raycasting/raycasting_draw.c
void			cast_rays(t_game *game);

// FUNCTION TEXTURING /-\ srcs/texturing/init_textures.c
void			init_textures(t_game *game);
unsigned int	get_texture_color(t_texture *texture, int x, int y);
void			load_texture(t_game *game, t_texture *texture, char *path);

// FUNCTION PLAYER /-\ srcs/player/intit_player_controls.c
int				ft_update_game(void *param);
void			init_player(t_game *game);

// FUNCTION PLAYER /-\ srcs/player/player_movement.c
void			init_move(t_move *move, t_game *game,
					double dir_x, double dir_y);
void			check_horizontal(t_move *move, t_game *game, double dir_x);
void			check_vertical(t_move *move, t_game *game, double dir_y);

// FUNCTION PLAYER /-\ srcs/player/player_init_movement.c
void			move_forward(t_game *game);
void			move_backwards(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);

// FUNCTION PLAYER /-\ srcs/player/rotate.c
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			rotate_player(t_game *game, double angle);
int				mouse_move(int x, int y, void *param);

// FUNCTION PLAYER /-\ srcs/player/keys.c
int				key_release(int keycode, void *param);
int				key_press(int keycode, void *param);

// FUNCTION UTILS /-\ srcs/utils/function_utils.c
int				ft_strlen_find(char *str, char c);
int				ft_count_index(char **input);
double			get_time(void);

// FUNCTION UTILS MLX /-\ srcs/utils-mlx/function_mlx.c
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

// FUNCTION UTILS /-\ srcs/utils/parsing_utils.c
bool			ft_only_espace(const char *line);
bool			ft_only_iswall(const char *line);
int				ft_malloc_size(char *argv);
int				ft_check_dir(t_game *game);

// FUNCTION BONUS /-\ srcs/bonus/minimap.c
void			draw_minimap(t_game *game);
void			chose_color_tiles_and_draw_it(t_game *game,
					t_coord coord, t_coord pixel);
int				ft_isspace(char c);

// FUNCTION UI /-\ srcs/ui/main_menu.c
void			ft_main_menu(t_game *game);
int				ft_mouse_click(int button, int x, int y, void *param);
int				ft_space_press(int keycode, void *param);

#endif