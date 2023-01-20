#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libs/libs.h"
# include "./libs/libmlx/include/MLX42/MLX42.h"

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

	mlx_image_t		*map_img;
	char			**map;
	int				m_width;
	int				m_height;

	mlx_image_t		*player_img;
	int				p_width_pos;
	int				p_height_pos;

	mlx_image_t		*view_img;
	double				dir_x;
	double				dir_y;
	double				rotation;

	mlx_image_t		*test;

}				t_vars;

// parsing.c
void	initialize(char *mapfile, t_map **map);
void	parsing(t_map *map);
void	map_pars(t_map *map);

// read_map.c
void	get_finalmap(t_map *map, char *lastline);
void	countinglines(t_map *map, char *lastline);
void	getmap_content(t_map *map);

// check_map.c

// check_extenstion.c
int	check_extension(char *mapfile);

// movement.c
void	key_hook(mlx_key_data_t keydata, void *param);

// init.c
void init_window(t_vars *vars);
void init_player(t_vars *vars);
void view_starting_direction(t_vars *vars);

#endif
