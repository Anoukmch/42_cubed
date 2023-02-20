#include "../includes/cub3d.h"

void	rotate_calculation(t_vars *vars)
{
	double	old;

	old = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(vars->rotation)
		- vars->dir_y * sin(vars->rotation);
	vars->dir_y = old * sin(vars->rotation)
		+ vars->dir_y * cos(vars->rotation);
	old = vars->planex;
	vars->planex = vars->planex * cos(vars->rotation)
		- vars->planey * sin(vars->rotation);
	vars->planey = old * sin(vars->rotation)
		+ vars->planey * cos(vars->rotation);
}

void	rotation(t_vars *vars, char *str)
{
	if (!ft_strcmp(str, "right"))
		vars->rotation = 0.0872665;
	else if (!ft_strcmp(str, "left"))
		vars->rotation = -0.0872665;
	rotate_calculation(vars);
}

int	check_corners(t_vars *vars, double x, double y)
{
	if (vars->finalmap[(int)y][(int)x] == '0'
		&& ((int)vars->player_x != (int)x
			|| (int)vars->player_y != (int)y))
	{
		if (vars->player_x < x && vars->player_y < y
			&& vars->finalmap[(int)y][(int)x - 1] == '1'
			&& vars->finalmap[(int)y - 1][(int)x] == '1')
			return (1);
		else if (vars->player_x > x && vars->player_y > y
			&& vars->finalmap[(int)y][(int)x + 1] == '1'
			&& vars->finalmap[(int)y + 1][(int)x] == '1')
			return (1);
		else if (vars->player_x < x && vars->player_y > y
			&& vars->finalmap[(int)y][(int)x - 1] == '1'
			&& vars->finalmap[(int)y + 1][(int)x] == '1')
			return (1);
		else if (vars->player_x > x && vars->player_y < y
			&& vars->finalmap[(int)y][(int)x + 1] == '1'
			&& vars->finalmap[(int)y - 1][(int)x] == '1')
			return (1);
	}
	return (0);
}

bool	movement_hit_wall(t_vars *vars, int direction)
{
	double	x;
	double	y;

	if (direction == NO)
	{
		x = vars->player_x + vars->dir_x * 0.2;
		y = vars->player_y + vars->dir_y * 0.2;
	}
	if (direction == SO)
	{
		x = vars->player_x - vars->dir_x * 0.2;
		y = vars->player_y - vars->dir_y * 0.2;
	}
	if (direction == EA)
	{
		x = vars->player_x - vars->dir_y * 0.2;
		y = vars->player_y + vars->dir_x * 0.2;
	}
	if (direction == WE)
	{
		x = vars->player_x + vars->dir_y * 0.2;
		y = vars->player_y - vars->dir_x * 0.2;
	}
	if (vars->finalmap[(int)y][(int)x] == '1'
		|| check_corners(vars, x, y))
		return (1);
	return (0);
}

