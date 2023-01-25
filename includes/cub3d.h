#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libs/libs.h"
# include "./libs/libmlx/include/MLX42/MLX42.h"

# define TEXTURES			1
# define WALL				0

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

	// SIDE VIEWS
	double			fov;
	double			left_x;
	double			left_y;
	double			right_x;
	double			right_y;
	double			camerax;
	double			cameray;
	char			**finalmap;

}				t_vars;

// init.c
void	init_window(t_vars *vars, t_map *map);
void	init_player_and_views(t_vars *vars);
void	view_starting_direction(t_vars *vars);
void	sidesofview(t_vars *vars);

// parsing.c
void	initialize(char *mapfile, t_map **map);
void	parsing(t_map *map);
void	map_pars(t_map *map);

// error_exit.c
int error_exit(char *s);

// read_map.c
void	get_finalmap(t_map *map, char *lastline);
void	countinglines(t_map *map, char *lastline);
void	getmap_content(t_map *map);

// check_map.c

// put_map_to_window.c
void	init_map(t_vars *vars, t_map *map);

// check_extenstion.c
int	check_extension(char *mapfile);

// movement.c
void	key_hook(mlx_key_data_t keydata, void *param);
void	get_view(t_vars *vars, int color, double x, double y);

void	dda(t_vars *vars);

#endif
