#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libs/libs.h"
# include "./libs/libmlx/include/MLX42/MLX42.h"

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

// movement.c
void	key_hook(mlx_key_data_t keydata, void *param);

// init.c
void init_window(t_vars *vars);
void init_player(t_vars *vars);
void view_starting_direction(t_vars *vars);
#endif