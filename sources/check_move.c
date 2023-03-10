/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:03:35 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/28 13:43:34 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_calculation(t_vars *vars)
{
	double	old;

	old = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(vars->rotation)
		- vars->dir_y * sin(vars->rotation);
	vars->dir_y = old * sin(vars->rotation)
		+ vars->dir_y * cos(vars->rotation);
	old = vars->plane_x;
	vars->plane_x = vars->plane_x * cos(vars->rotation)
		- vars->plane_y * sin(vars->rotation);
	vars->plane_y = old * sin(vars->rotation)
		+ vars->plane_y * cos(vars->rotation);
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
	if ((vars->finalmap[(int)y][(int)x] != '1'
		|| !vars->finalmap[(int)y][(int)x])
		&& ((int)vars->player_x != (int)x
			|| (int)vars->player_y != (int)y))
	{
		if (vars->player_x < x && vars->player_y < y
			&& !one_two(vars->finalmap[(int)y][(int)x - 1])
			&& !one_two(vars->finalmap[(int)y - 1][(int)x]))
			return (1);
		else if (vars->player_x > x && vars->player_y > y
			&& !one_two(vars->finalmap[(int)y][(int)x + 1])
			&& !one_two(vars->finalmap[(int)y + 1][(int)x]))
			return (1);
		else if (vars->player_x < x && vars->player_y > y
			&& !one_two(vars->finalmap[(int)y][(int)x - 1])
			&& !one_two(vars->finalmap[(int)y + 1][(int)x]))
			return (1);
		else if (vars->player_x > x && vars->player_y < y
			&& !one_two(vars->finalmap[(int)y][(int)x + 1])
			&& !one_two(vars->finalmap[(int)y - 1][(int)x]))
			return (1);
	}
	return (0);
}

void	possible_new_position(t_vars *vars, int direction)
{
	if (direction == W)
	{
		vars->tmp_x = vars->player_x + vars->dir_x * 0.3;
		vars->tmp_y = vars->player_y + vars->dir_y * 0.3;
	}
	if (direction == S)
	{
		vars->tmp_x = vars->player_x - vars->dir_x * 0.3;
		vars->tmp_y = vars->player_y - vars->dir_y * 0.3;
	}
	if (direction == D)
	{
		vars->tmp_x = vars->player_x - vars->dir_y * 0.3;
		vars->tmp_y = vars->player_y + vars->dir_x * 0.3;
	}
	if (direction == A)
	{
		vars->tmp_x = vars->player_x + vars->dir_y * 0.3;
		vars->tmp_y = vars->player_y - vars->dir_x * 0.3;
	}
}

bool	movement_hit_wall(t_vars *vars, int direction)
{
	possible_new_position(vars, direction);
	if (vars->finalmap[(int)vars->tmp_y][(int)vars->tmp_x] == '1'
		|| vars->finalmap[(int)vars->tmp_y][(int)vars->tmp_x] == '2'
		|| check_corners(vars, vars->tmp_x, vars->tmp_y))
		return (1);
	return (0);
}
