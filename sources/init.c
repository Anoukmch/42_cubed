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
			vars->m_height * 32, "Cub3D", true);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
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
			if (vars->finalmap[height][width] == 'N'
				|| vars->finalmap[height][width] == 'E'
				|| vars->finalmap[height][width] == 'S'
				|| vars->finalmap[height][width] == 'W')
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

// CHANGE VECTORS TO START IN ANOTHER DIRECTION
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
// 1.15192; //angle of 66 degrees
// NORTH
void	init_player_and_views(t_vars *vars)
{
	get_player_position(vars);
	vars->fov = 1.15192;
	vars->dir_x = 0;
	vars->dir_y = -1;
	vars->planex = 0.66;
	vars->planey = 0;
	vars->image_3d = mlx_new_image(vars->mlx,
			vars->m_width * 32, vars->m_height * 32);
	mlx_image_to_window(vars->mlx, vars->image_3d, 0, 0);
}

// BLUE: 0xA6C0;
// WHITE: 0xFFFFFFFF;
// GREEN: 0x00993366;
// ORANGE: 0xFF993366;
// YELLOW: 0xFFFF007F;
// PINK: 0xFF006699;
