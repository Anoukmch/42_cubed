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

# define DOOR_TEXT_PATH	"/Users/amechain/source/projects/rank04/42_cubedbis/pngfiles/living.png"

# define W	0
# define D	1
# define S	2
# define A	3

# define BPP			4
# define X_SIDE_NO_S0	0
# define Y_SIDE_EA_WE	1

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
	int				door_x;
	int				door_y;
	double			perp_wall_dist_2;

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

// init.c
void		init_vars(t_vars *vars, t_map *map);
void		init_window(t_vars *vars, t_map *map);
void		init_player_and_views(t_vars *vars);
void		init_map(char *mapfile, t_map *map);

// parsing.c
void		parse_text_and_color(t_map *map);
int			check_identifier(t_map *map);
void		fill_var(char *line, t_map *map);
int			check_range_colors(char *line, int indic);
int			check_color_comb(char *line);

// utils_free.c
int			free_array(char **array, int ret_stat);
void		delete_txt(t_vars *vars, int alloc_txt);
void		free_text_img(t_vars *vars);
void		free_struct(t_map *map);

// utils.parser.c
void		check_comma(char *line);
int			size_2d_array(char **array);
int			isdigit_string(char	*str);
void		check_first_and_last(char *str);

// error_exit.c
int			error_exit(char *s);

// read_map.c
void		get_map(t_map *map);
void		countinglines(t_map *map);
void		getmap_content(t_map *map);

// check_map.c
void		map_pars(t_map *map);

// check_extension.c
int			check_extension(char *mapfile);

// movement.c
void		windowresize(int32_t width, int32_t height, void *param);
void		key_hook(void *param);
bool		movement_hit_wall(t_vars *vars, int direction);

// dda.c
void		dda(void *param);

// colors.c
void		transform_colors(t_vars *vars, t_map *map);
uint32_t	get_colour(char *s);

// get_map.c
char		*ft_free_strtrim(char *s1, char const *set);

// windowresize.c
void		windowresize(int32_t width, int32_t height, void *param);

// texture.c
void		init_textures(t_vars *vars, t_map *map);

// draw_textures.c
void		draw_everything(t_cast *t, t_vars *vars);
int			texture_x_value(mlx_texture_t *tex, t_cast *t, t_vars *vars);

// trying_rendering.c
void		print_textures(t_cast *t, t_vars *vars, int color);
void		walking_directions(t_vars *vars);
void		rotation(t_vars *vars, char *str);

// player.c
void		get_player_position(t_vars *vars);
void		get_player_startingview_x_dir(t_vars *vars);
void		get_player_startingview_y_dir(t_vars *vars);

#endif
