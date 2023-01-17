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

typedef struct s_map
{
	int	fd;
	char	*read_line;

	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;

	char	*rgb_f;
	char	*rgb_c;

}			t_map;


typedef struct s_vars
{
	mlx_t			*mlx;

	mlx_texture_t	*textures[TEXTURES];

	mlx_image_t		*bg_img;

	mlx_image_t		*map_img;
	char			**map;
	int				m_width;
	int				m_height;

	mlx_image_t		*player_img;
	int				p_width;
	int				p_height;

	int				coll_counter;
	int				steps;

	int				coll_no;
	int				player_no;
	int				exit_no;

}				t_vars;

void	ft_init_textures(t_vars *vars);
void	check_texturesize(t_vars *vars);
int		countinglines(char **argv);
void	readingmap(char **argv, t_vars *vars);
void	set_player_pos(t_vars *vars);

void	paintingmap(t_vars *vars);
void	paintingwalls(t_vars *vars, int height, int width);
void	paintingcorners(t_vars *vars, int height, int width);

void	playermovement(t_vars *vars);
void	playerright(t_vars *vars);
void	playerleft(t_vars *vars);
void	playerdown(t_vars *vars);
void	playerup(t_vars *vars);
void	exit_and_collectible(t_vars *vars);

void	counting_character(t_vars *vars, int w, int h);
void	rectangle_check(t_vars *vars);
void	errorhandling(t_vars *vars, int w, int h);
void	exit_and_free(t_vars *vars, int status);

int	check_extension(char *mapfile);

#endif
