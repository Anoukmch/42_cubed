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

void	get_view_until(t_vars *vars, int color, double x, double y)
{
	int	i;

// 	i = 1;
// 	while ((vars->p_height_pos * 32) + 16 + (y * i) < ((vars->p_height_pos + 0.66) * 32) + 16
// 		&& (vars->p_height_pos * 32) + 16 + (y * i) > ((vars->p_height_pos + 0.66) * 32) + 16)
// 	{
// 		mlx_put_pixel(vars->player_img, (vars->p_width_pos * 32) + 16 + (x * i),
// 			(vars->p_height_pos * 32) + 16 + (y * i), color);
// 		i++;
// 	}
// }

void	init_player_and_views(t_vars *vars)
{
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
	vars->player_img = mlx_new_image(vars->mlx, vars->m_width * 32 * 2, vars->m_height * 32 * 2);
	mlx_put_pixel(vars->player_img, vars->p_width_pos * 32 + 16, vars->p_height_pos * 32 + 16, 0xA6C0);
	get_view(vars, 255, vars->dir_x, vars->dir_y);
	// GET SIDES OF FOV
	sidesofview(vars);
	get_view(vars, 255, vars->left_x, vars->left_y);
	get_view(vars, 255, vars->right_x, vars->right_y);
	get_view_until(vars, 0xA6C0, vars->planex, vars->planey);
	get_view_until(vars, 0xA6C0, vars->planex * (-1), vars->planey * (-1));
	// dda(vars);
	mlx_image_to_window(vars->mlx, vars->player_img, 0, 0);
}
