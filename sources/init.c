#include "../includes/cub3d.h"

int	find_longest_mapline(t_map *map)
{
	size_t	longest;
	int		i;

	i = 0;
	longest = ft_strlen(map->cmap[i]);
	while (map->cmap[i++])
	{
		if (longest < ft_strlen(map->cmap[i]))
			longest = ft_strlen(map->cmap[i]);
	}
	return ((int)longest);
}

void	init_window(t_vars *vars, t_map *map)
{
	vars->m_width = find_longest_mapline(map);
	vars->m_height = map->maplines + 1;
	vars->mlx = mlx_init(vars->m_width * 32,
			vars->m_height * 32, "Cub3D", true); //opening a window
	if (!vars->mlx)
		exit(EXIT_FAILURE);
}

void	sidesofview(t_vars *vars)
{
	double	old;
	double	left_rot;
	double	right_rot;

	left_rot = (-1) * (vars->fov / 2);
	right_rot = vars->fov / 2;
	old = vars->dir_x;
	// LEFT SIDE
	vars->left_x = vars->dir_x * cos(left_rot)
		- vars->dir_y * sin(left_rot);
	vars->left_y = old * sin(left_rot)
		+ vars->dir_y * cos(left_rot);
	// RIGHT SIDE
	vars->right_x = vars->dir_x * cos(right_rot)
		- vars->dir_y * sin(right_rot);
	vars->right_y = old * sin(right_rot)
		+ vars->dir_y * cos(right_rot);
}

void    get_view_until(t_vars *vars, uint32_t color, double x, double y)
{
    int i;
    i = 0;
    while ((x * i) < 0.66 * 32 && (x * i) > -0.66 * 32
        && (y * i) < 0.66 * 32 && (y * i) > -0.66 * 32)
    {
        mlx_put_pixel(vars->player_img, (vars->player_x * 32) + (x * i),
            (vars->player_y * 32) + (y * i), color);
        i++;
    }
}

void	get_player_position(t_vars *vars)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (vars->finalmap[height])
	{
		while (vars->finalmap[height][width])
		{
			if (vars->finalmap[height][width] == 'N' || vars->finalmap[height][width] == 'E'
				|| vars->finalmap[height][width] == 'S' || vars->finalmap[height][width] == 'W')
			{
				vars->player_x = width;
				vars->player_y = height;
			}
			width++;
		}
		height++;
		width = 0;
	}
}

void	init_player_and_views(t_vars *vars)
{
	get_player_position(vars);
	vars->fov = 1.15192; //angle of 66 degrees
	// CHANGE VECTORS TO START IN ANOTHER DIRECTION
	// NORTH
	vars->dir_x = 0;
	vars->dir_y = -1;
	vars->planex = 0.66;
	vars->planey = 0;
	// EAST
	// vars->dir_x = 1;
	// vars->dir_y = 0;
	// vars->camerax = 0;
	// vars->cameray = 0.66;
	// SOUTH
	// vars->dir_x = 0;
	// vars->dir_y = 1;
	// vars->camerax = 0.66;
	// vars->cameray = 0;
	// WEST
	// vars->dir_x = -1;
	// vars->dir_y = 0;
	// vars->camerax = 0;
	// vars->cameray = 0.66;
	vars->image_3d = mlx_new_image(vars->mlx, vars->m_width * 32, vars->m_height * 32);
	mlx_image_to_window(vars->mlx, vars->image_3d, 0, 0);
}

// BLUE: 0xA6C0;
// WHITE: 0xFFFFFFFF;
// GREEN: 0x00993366;
// ORANGE: 0xFF993366;
// YELLOW: 0xFFFF007F;
// PINK: 0xFF006699;
