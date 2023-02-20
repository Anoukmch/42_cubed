#include "../includes/cub3d.h"

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
		vars->plane_x = 0.66;
		vars->plane_y = 0;
	}
	if (vars->finalmap[(int)vars->player_y][(int)vars->player_x] == 'S')
	{
		vars->dir_x = 0;
		vars->dir_y = 1;
		vars->plane_x = -0.66;
		vars->plane_y = 0;
	}
}

void	get_player_startingview_y_dir(t_vars *vars)
{
	if (vars->finalmap[(int)vars->player_y][(int)vars->player_x] == 'E')
	{
		vars->dir_x = 1;
		vars->dir_y = 0;
		vars->plane_x = 0;
		vars->plane_y = 0.66;
	}
	if (vars->finalmap[(int)vars->player_y][(int)vars->player_x] == 'W')
	{
		vars->dir_x = -1;
		vars->dir_y = 0;
		vars->plane_x = 0;
		vars->plane_y = -0.66;
	}
}
