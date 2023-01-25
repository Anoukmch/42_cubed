#include "../includes/cub3d.h"

void	get_view(t_vars *vars, int color, double x, double y)
{
	int	i;

	i = 1;
	while ((vars->player_y * 32) + 16 + (y * i) < vars->m_height * 32
		&& (vars->player_y * 32) + 16 + (y * i) > 0
		&& (vars->player_x * 32) + 16 + (x * i) < vars->m_width * 32
		&& (vars->player_x * 32) + 16 + (x * i) > 0)
	{
		mlx_put_pixel(vars->player_img, (vars->player_x * 32) + 16 + (x * i),
			(vars->player_y * 32) + 16 + (y * i), color);
		i++;
	}
}
	// while (16 + (y * i) < vars->m_height * 32
	// 	&& 16 + (y * i) > 0
	// 	&& 16 + (x * i) < vars->m_width * 32
	// 	&& 16 + (x * i) > 0)

void rotate_calculation(t_vars *vars)
{
	double	old;

	old = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(vars->rotation)
		- vars->dir_y * sin(vars->rotation);
	vars->dir_y = old * sin(vars->rotation)
		+ vars->dir_y * cos(vars->rotation);
}

// SKALARPRODUKT
void	rotation(t_vars *vars, char *str)
{
	// int tmp_x;
	// int tmp_y;

	if (!ft_strcmp(str, "right"))
		vars->rotation = 0.0174533;
	else if (!ft_strcmp(str, "left"))
		vars->rotation = -0.0174533;
	get_view(vars, 0, vars->dir_x, vars->dir_y);
	get_view(vars, 0, vars->left_x, vars->left_y);
	get_view(vars, 0, vars->right_x, vars->right_y);
	rotate_calculation(vars);
	sidesofview(vars);
	get_view(vars, 255, vars->dir_x, vars->dir_y);
	get_view(vars, 255, vars->left_x, vars->left_y);
	get_view(vars, 255, vars->right_x, vars->right_y);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		vars->player_img->instances[0].y -= 3;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		vars->player_img->instances[0].y += 3;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		vars->player_img->instances[0].x -= 3;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		vars->player_img->instances[0].x += 3;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotation(vars, "right");
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotation(vars, "left");
}
