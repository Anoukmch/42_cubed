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
void    get_view(t_vars *vars, uint32_t color, double x, double y);
void    get_view_until(t_vars *vars, uint32_t color, double x, double y);

void	dda(void *param);
void	draw_line(void *win, int beginX, int beginY, int endX, int endY, int color);
void	dda_overwriting(t_vars *vars);

// colors.c
void	transform_colors(t_vars *vars, t_map *map);

// get_map.c
char	*ft_free_strtrim(char *s1, char const *set);

// windowresize.c
void	windowresize(int32_t height, int32_t width, void *param);

#endif
