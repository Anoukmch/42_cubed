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
	map = (t_map *)map;
	vars->w_width = 1200;
	vars->w_height = 700;
	vars->mlx = mlx_init(vars->w_width,
			vars->w_height, "Cub3D", true);
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
				vars->player_x = width + 0.5;
				vars->player_y = height + 0.5;
			}
			width++;
		}
		height++;
		width = 0;
	}
}

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
	vars->m_width = vars->w_width;
	vars->m_height = vars->w_height;
	vars->fov = 1.15192;
	get_player_startingview_x_dir(vars);
	get_player_startingview_y_dir(vars);
	vars->image_3d = mlx_new_image(vars->mlx,
			vars->m_width, vars->m_height);
	mlx_image_to_window(vars->mlx, vars->image_3d, 0, 0);
}
