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
	vars->longestline = find_longest_mapline(map);
	vars->w_width = (vars->longestline) * 32;
	vars->w_height = (map->maplines + 1) * 32;
	vars->mlx = mlx_init(vars->w_width,
			vars->w_height, "Cub3D", true);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
}

void	init_textures(t_vars *vars, t_map *map)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		vars->textures[i] = mlx_load_png(map->text_path[i]);
		if (vars->textures[i] == NULL)
		{
			delete_txt(vars, i);
			error_exit("Please check the initialization of your textures!\n");
		}
		i++;
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

void	init_vars(t_vars *vars, t_map *map)
{
	init_window(vars, map);
	init_textures(vars, map);
	init_player_and_views(vars);
}
