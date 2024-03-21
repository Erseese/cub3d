/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouihar <ytouihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:20:53 by bsuc              #+#    #+#             */
/*   Updated: 2024/03/21 18:32:56 by ytouihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/headers/libft.h"
# include "../libft/headers/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <math.h>
# include <errno.h>
# include <time.h>

/*       ERROR                          */
# define BOLD "\x1b[1m"
# define RED "\x1b[31m"
# define RESET "\x1b[0m"

/*       PARSING                        */
# define UP 1
# define DOWN 3
# define LEFT 2
# define RIGHT 4
# define NORTH 5
# define SOUTH 6
# define EAST 7
# define WEST 8

/*       GAME                          */
# define WIN_WIDTH 640
# define WIN_HEIGHT 400
# define CENTER_H (WIN_HEIGHT / 2)
# define CENTER_W (WIN_WIDTH / 2)
# define DIST_VIEW ((WIN_WIDTH / 2) / tan(FOV_RAD / 2))
# define FOV 60
# define IMG_SIZE 64.
# define PLAY_HEIGHT 32 // ??
# define PLAYER_SPEED 10
# define PLAYER_WIDTH 8
# define MINIMAP_SIZE WIN_HEIGHT / 6
# define MINIMAP_BLOCK 9.0
# define PistolW 99
# define PistolH 88
# define FOV_RAD M_PI / 3

typedef struct s_file
{
	char			*line;
	struct s_file	*next;
}	t_file;

typedef struct s_parse
{
	char	**map;
	char	**map_copy;

	char	*north;
	char	*south;
	char	*east;
	char	*west;

	t_file	*init;

	int		f_red;
	int		f_green;
	int		f_blue;

	int		c_red;
	int		c_green;
	int		c_blue;

	int		player_position;

	int		len_y;
}	t_parse;

typedef struct s_coor
{
	double	x;
	double	y;
}	t_coor;

typedef struct s_mlx
{
	void	*img;
	void	*addr;

	int		bpp;
	int		l_len;
	int		endian;
}	t_mlx;

typedef struct s_door
{
	int				id;
	int				startx;
	int				starty;
	int				endx;
	int				endy;
	int				px;
	int				py;
	int				endpx;
	int				endpy;
	long			time;
	int				open;
	struct s_door	*next;
}				t_door;

typedef struct s_data
{
	int y;
	int i;
	int	j;
	unsigned int color;
	int offset;
	t_mlx text;
	char	**copy_map;
	int		index;
	int		index_j;
} t_data;

typedef struct s_color
{
	unsigned int	r;
	unsigned int	b;
	unsigned int	g;
	unsigned int	t;
}	t_color;

typedef struct s_game
{
	t_parse	*parsing;

	void	*mlx;
	void	*win;

	t_mlx	text[4];
	t_mlx	img;

	int		floor;
	int		ceiling;

	t_coor	hit_wall;

	int		pos_x;
	int		pos_y;
	double	play_x;
	double	play_y;
	double	play_ang;
	double	fov_ang;
	double	ray_ang;
	double	distance;

	t_mlx	door;
	t_mlx	pistol;
	t_door	*doors;
	t_mlx	mini_img;
	long	start_timer;
	double	curr_ang;
	int		minimap_size;
	int		mousex;
	int		longline;
	int		hide;
	double	intensity;
}	t_game;

/***************************************************/
/*                   PARSING                       */
/***************************************************/
/**/
/*                   PARSING.C                     */
t_parse			*parsing(char **argv);
int				trim_backslashn(t_file *init);

/*                   PARSING_UTILS.C               */
void			check_end_parse(t_parse *parsed, t_file *init, int index);
int				ft_inisize(t_file *lst);
t_parse			*initalizeparse(void);
int				skip_nb_and_spaces(int index, t_parse *parsed, t_file *init);
int				ft_strlen_matrice(char **map);

/*                   PARSING_UTILS2.C                */
int				file_len(t_file *file);
void			empty_init(t_file *init);
int				check_border(char **copy_map);
int				line_copy(t_data *d, int i, int j, char **map);

/*                   PARSING_CHARS.C               */
void			fill_struct(t_parse *parsed, t_file *init);

/*                   PARSING_STRUCT.C                 */
void			get_cubfile(t_file **init, char *file);

/*                   PARSING_MAP.C                 */
int				parsing_map(t_parse *parsed);
int				check_correct_walls(char **map, int x, int y, int type);

/*                   RIGHT_SIDE.C                  */
int				find_longest_line(char **map, int *i);
char			**copy_right_with_spaces(char **map, int i, int j);
int				handle_right(char **copy_map);

/*                   PARSING_MAP2.C                */
int				check_inside(t_parse *parsed, char **copy_map);

/*                   PARSING_SANITIZE.C            */
void			free_struct(t_file *init);
void			errorfunctionparse(t_parse *parsed, char *message);
void			free_map(char **map);
void			free_parse(t_parse *parsed);

/***************************************************/
/*                      EXEC                       */
/***************************************************/
/**/
/*                    GAME_INIT_C                  */
void			game_init(t_game *game, t_parse *p);

/*                   MLX_PIXEL_C                 */
unsigned int	pixel_get(t_mlx *img, int x, int y);
void			my_mlx_pixel_put(t_mlx *img, int x, int y, int color);

/*                   RAYCASTING.C                 */
double			get_horiz_inter(t_game *game, double curr_ang, double s);
double			get_verti_inter(t_game *game, double curr_ang, double c);

/*                   GET_DISTANCE.C               */
int				eval_distance(t_game *game);

/*                   RENDER.C                     */
int				render(t_game *game);

/*                   HIT_WALL.C                    */
int				hit_wall(t_game *game, t_coor *move);

/*                   KEY_EVENT.C                   */
int				get_key_event(int keycode, t_game *game);

/*                   TRIGO_UTILS.C                 */
void			eval_move(t_game *game, t_coor *move, int dir);
void			eval_step(double curr_ang, double *step, int x);
void			check_max_trigo(double ang);

/*                   SANITIZE_C                    */
void			handle_error(const char *s, t_parse *parsing, int ex);
void			free_ptr(t_game *game);
int				win_exit(t_game *game);



//bonus :
/*                   game_init_utils_bonus.c                    */
void			game_init_bonus(t_game *game);
void			check_pas_mes_ennemis(t_game *game);
int				find_enemy(t_game *game, t_coor step, t_coor pos_ray, int test);
void			minimap(char **map, t_game *game);
void			doors_state(t_game *game);
void			pistol(t_game *game);
void			cursor(t_game *game);
void			govalo(t_game *game);
int				find_door(t_game *game, t_coor step, t_coor *pos_ray, int test);
unsigned int	colorize(unsigned int color, double fog);
long			get_current_time(long times);
void			open_door(t_game *game);
double			get_distance(t_game *game, t_coor *inter);
void			get_hit_wall(t_game *game);
void			print_door(t_game *game, double curr_ang, double v_inter_dist, int ray);
char			**map_copy(char **map);

#endif