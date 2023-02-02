#include "../includes/cub3d.h"

void	get_view(t_vars *vars, uint32_t color, double x, double y)
{
	int	i;

	i = 1;
	while ((vars->player_y * 32) + (y * i) < vars->m_height * 32 * 2
		&& (vars->player_y * 32) + (y * i) > 0
		&& (vars->player_x * 32) + (x * i) < vars->m_width * 32 * 2
		&& (vars->player_x * 32) + (x * i) > 0)
	{
		mlx_put_pixel(vars->player_img, (vars->player_x * 32) + (x * i),
			(vars->player_y * 32) + (y * i), color);
		i++;
	}
}

void rotate_calculation(t_vars *vars)
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

// SKALARPRODUKT
void	rotation(t_vars *vars, char *str)
{
	if (!ft_strcmp(str, "right"))
		vars->rotation = 0.0872665; //1 degree
	else if (!ft_strcmp(str, "left"))
		vars->rotation = -0.0872665; //1 degree
	dda_overwriting(vars);
	rotate_calculation(vars);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		dda_overwriting(vars);
		vars->player_x += vars->dir_x * 0.1;
		vars->player_y += vars->dir_y * 0.1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		dda_overwriting(vars);
		vars->player_x -= vars->dir_x * 0.1;
		vars->player_y -= vars->dir_y * 0.1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		dda_overwriting(vars);
		vars->player_x -= vars->dir_x * 0.1;
		vars->player_y += vars->dir_y * 0.1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		dda_overwriting(vars);
		vars->player_x += vars->dir_x * 0.1;
		vars->player_y -= vars->dir_y * 0.1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotation(vars, "right");
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotation(vars, "left");
}
