#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libs/libs.h"
# include "./libs/libmlx/include/MLX42/MLX42.h"

# define TEXTURES		5

# define NO	0
# define EA	1
# define SO	2
# define WE	3
# define DOOR	4

# define DOOR_TEXT_PATH	"pngfiles/door1.png"

# define W	0
# define D	1
# define S	2
# define A	3

# define BPP			4
# define X_SIDE_NO_S0	0
# define Y_SIDE_EA_WE	1

# define MINIPIX 8

# define RGB_BLUE	0x02FFF1FF
# define RGB_WHITE	0xFFFFFFFF
# define RGB_GREEN	0x009966FF
# define RGB_YELLOW	0xFFFF007F
# define RGB_BROWN	0x533000FF
# define RGB_PINK	0xFF006FFF

typedef struct s_map
{
	int		fd;
	char	*line;
	char	**text_path;
	char	*rgb_f;
	char	*rgb_c;
	char	*m_argv;
	char	**cmap;
	int		maplines;
	int		mapstart;
	int		player;

}			t_map;

typedef struct s_vars
{
	mlx_t			*mlx;
	mlx_texture_t	*textures[TEXTURES];
	double			w_width;
	double			w_height;
	double			m_width;
	double			m_height;
	double			player_x;
	double			player_y;
	double			dir_x;
	double			dir_y;
	double			rotation;
	uint32_t		floorcolor;
	uint32_t		ceilingcolor;
	double			fov;
	double			plane_x;
	double			plane_y;
	char			**finalmap;
	double			tmp_x;
	double			tmp_y;
	mlx_image_t		*image_3d;
	int				linesofmap;
	int				longestline;
	double			mini_w_width;
	double			mini_w_height;
	double			mini_cube_w;
	double			mini_cube_h;
	mlx_image_t		*image_2d;

}				t_vars;

typedef struct s_cast
{
	int			x;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		step_x;
	double		step_y;
	int			hit;
	int			door;
	int			is_ea_we;
	double		perp_wall_dist;
	int			which_card_pt;
	int			wall_line;
	int			draw_start;
	int			draw_end;
	int			iter;

}	t_cast;

// init_vars.c
void		init_vars(t_vars *vars, t_map *map);

// init_map.c
void		init_map(char *mapfile, t_map *map);

// parse_text_and_color.c
void		parse_text_and_color(t_map *map);

// utils_free.c
int			free_array(char **array, int ret_stat);
void		delete_txt(t_vars *vars, int alloc_txt);
void		free_text_img(t_vars *vars);
void		free_struct(t_map *map);

// utils_parser.c
void		check_comma(char *line);
int			size_2d_array(char **array);
int			isdigit_string(char	*str);
void		check_first_and_last(char *str);

// utils_dda.c
int			one_two(char c);

// error_exit.c
int			error_exit(char *s);

// read_map.c
void		countinglines(t_map *map);
void		getmap_content(t_map *map);

// check_map.c & check_map_2.c
void		map_pars(t_map *map);
void		check_doors(char **map, int i);

// check_extension.c
int			check_extension(char *mapfile);

// check_move.c
bool		movement_hit_wall(t_vars *vars, int direction);
void		rotation(t_vars *vars, char *str);

// dda.c
void		dda(void *param);

// colors.c
void		transform_colors(t_vars *vars, t_map *map);

// get_map.c
void		get_map(t_map *map);

// event_handling.c
void		windowresize(int32_t width, int32_t height, void *param);
void		key_hook(void *param);

// texture.c
void		init_textures(t_vars *vars, t_map *map);

// draw_textures.c
void		draw_everything(t_cast *t, t_vars *vars);
void		draw_wall_and_ceiling(t_cast *t, t_vars *vars);
// player.c
void		get_player_position(t_vars *vars);
void		get_player_startingview_x_dir(t_vars *vars);
void		get_player_startingview_y_dir(t_vars *vars);

// minimap.c
void		init_minimap(t_vars *vars);
void		draw_rays_minimap(t_cast *t, t_vars *vars, uint32_t color);
void		draw_minimap(t_vars *vars, char **map);
void		paintingmap(t_vars *vars, char **map);

#endif
