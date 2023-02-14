#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libs/libs.h"
# include "./libs/libmlx/include/MLX42/MLX42.h"

# define TEXTURES			13

# define PLAYER				0
# define SPACES				1
# define CORNER_LEFT_UP		2
# define CORNER_LEFT_DOWN 	3
# define CORNER_RIGHT_UP 	4
# define CORNER_RIGHT_DOWN 	5
# define WALL_LEFT 			6
# define WALL_RIGHT 		7
# define WALL_DOWN 			8
# define WALL_UP 			9
# define COLLECTS 			10
# define EXIT 				11
# define BOX 				12

#define NO	0
#define EA	1
#define SO	2
#define WE	3

typedef struct s_map
{
	int		fd;
	char	*read_line;

	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;

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

	mlx_image_t		*walls;
	mlx_texture_t	*textures[TEXTURES];
	mlx_image_t		*map_img;
	char			**map;
	int				m_width;
	int				m_height;

	mlx_image_t		*player_img;
	double				player_x;
	double				player_y;

	mlx_image_t		*view_img;
	double				dir_x;
	double				dir_y;
	double				rotation;

	uint32_t		floorcolor;
	uint32_t		ceilingcolor;
	// SIDE VIEWS
	double			fov;
	double			left_x;
	double			left_y;
	double			right_x;
	double			right_y;
	double			planex;
	double			planey;
	char			**finalmap;

	mlx_image_t		*image_3d;
	int				linesofmap;

}				t_vars;

typedef struct s_cast
{
	int x;
	double w;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int		mapX;
	int		mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double stepX;
	double stepY;
	int hit;
	int side;
	int i;
	int	is_negative;

	double perpWallDist;
	int side_2;

	int lineHeight; // h = the height in pixels of the screen
	double	h;

	int drawStart;
	int drawEnd;

	int	k;
	int	colorbool; //if 1 --> overwriting
	u_int32_t colors;
}	t_cast;

// init.c
void	init_window(t_vars *vars, t_map *map);
void	init_player_and_views(t_vars *vars);
void	initialize(char *mapfile, t_map **map);

// parsing.c
char	*texture_and_colors_pars(t_map *map);
int		check_identifier(char *line, t_map *map);
void	fill_var(char *line, t_map *map);
int		check_range_colors(char *line, int indic);
int		check_color_comb(char *line);

// utils_free.c
int	free_array(char **array, int ret_stat);

// utils.parser.c
void	check_comma(char *line);
int	size_2d_array(char **array);
int	isdigit_string(char	*str);

// error_exit.c
int error_exit(char *s);

// read_map.c
void	get_finalmap(t_map *map, char *lastline);
void	countinglines(t_map *map, char *lastline);
void	getmap_content(t_map *map);

// check_map.c

// check_extension.c
int	check_extension(char *mapfile);

// movement.c
void	key_hook(mlx_key_data_t keydata, void *param);

void	dda(void *param);
void	dda_overwriting(t_vars *vars);

// colors.c
void	transform_colors(t_vars *vars, t_map *map);
uint32_t	get_colour(char *s);

// get_map.c
char	*ft_free_strtrim(char *s1, char const *set);

// windowresize.c
void	windowresize(int32_t height, int32_t width, void *param);

// texture.c
void	init_textures(t_vars *vars);
int		check_texture_path(char *line, int indic);

// trying_rendering.c
void print_textures(t_cast *t, t_vars *vars, int color);

#endif
