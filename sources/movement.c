#include "../includes/cub3d.h"

void	get_view(t_vars *vars, int color)
{
	int	i;

	i = 1;
	while (vars->p_height_pos + (vars->dir_y * i) < vars->m_height * 2
		&& vars->p_height_pos + (vars->dir_y * i) > 0
		&& vars->p_width_pos + (vars->dir_x * i) < vars->m_width * 2
		&& vars->p_width_pos + (vars->dir_x * i) > 0)
	{
		mlx_put_pixel(vars->view_img, vars->p_width_pos + (vars->dir_x * i),
			vars->p_height_pos + (vars->dir_y * i), color);
		i++;
	}	
}

void rotate_calculation(t_vars *vars)
{
	double	olddir_x;

	olddir_x = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(vars->rotation)
		- vars->dir_y * sin(vars->rotation);
	vars->dir_y = olddir_x * sin(vars->rotation)
		+ vars->dir_y * cos(vars->rotation);	
}

// SKALARPRODUKT
void	rotation(t_vars *vars, char *str)
{
	if (!ft_strcmp(str, "right"))
		vars->rotation = 0.0174533;
	else if (!ft_strcmp(str, "left"))
		vars->rotation = -0.0174533;
	get_view(vars, 0);
	rotate_calculation(vars);
	get_view(vars, 255);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		vars->player_img->instances[0].y -= 32;
		vars->view_img->instances[0].y -= 32;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		vars->player_img->instances[0].y += 32;
		vars->view_img->instances[0].y += 32;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		vars->player_img->instances[0].x -= 32;
		vars->view_img->instances[0].x -= 32;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		vars->player_img->instances[0].x += 32;
		vars->view_img->instances[0].x += 32;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotation(vars, "right");
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotation(vars, "left");
}
