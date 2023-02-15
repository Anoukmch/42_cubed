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
// 1.15192; //angle of 66 degrees
void	get_player_startingview_x_dir(t_vars *vars)
{
	if (vars->finalmap[(int)vars->player_y][(int)vars->player_x] == 'N')
	{
		vars->dir_x = 0;
		vars->dir_y = -1;
		vars->planex = 0.66;
		vars->planey = 0;
	}
	if (vars->finalmap[(int)vars->player_y][(int)vars->player_x] == 'S')
	{
		vars->dir_x = 0;
		vars->dir_y = 1;
		vars->planex = -0.66;
		vars->planey = 0;
	}
}

void	get_player_startingview_y_dir(t_vars *vars)
{
	if (vars->finalmap[(int)vars->player_y][(int)vars->player_x] == 'E')
	{
		vars->dir_x = 1;
		vars->dir_y = 0;
		vars->planex = 0;
		vars->planey = 0.66;
	}
	if (vars->finalmap[(int)vars->player_y][(int)vars->player_x] == 'W')
	{
		vars->dir_x = -1;
		vars->dir_y = 0;
		vars->planex = 0;
		vars->planey = -0.66;
	}
}

void	init_player_and_views(t_vars *vars)
{
	get_player_position(vars);
	vars->fov = 1.15192;
	get_player_startingview_x_dir(vars);
	get_player_startingview_y_dir(vars);
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

void	initialize(char *mapfile, t_map **map)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		error_exit("Error\nAllocation fail");
	(*map)->fd = open(mapfile, O_RDONLY);
	if ((*map)->fd < 0)
		error_exit("Error\nOpen fail");
	(*map)->north_path = NULL;
	(*map)->south_path = NULL;
	(*map)->west_path = NULL;
	(*map)->east_path = NULL;
	(*map)->rgb_f = NULL;
	(*map)->rgb_c = NULL;
	(*map)->m_argv = mapfile;
	(*map)->player = 0;
}
