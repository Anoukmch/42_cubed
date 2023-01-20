#include "../includes/cub3d.h"

	// SKALARPRODUKT
void	rotate_left(t_vars *vars)
{
	int		i;
	double	olddir_x;

	i = 1;
	vars->rotation = -0.0174533;
	while (vars->p_height_pos + (vars->dir_y * i) < vars->m_height * 2
		&& vars->p_height_pos + (vars->dir_y * i) > 0
		&& vars->p_width_pos + (vars->dir_x * i) < vars->m_width * 2
		&& vars->p_width_pos + (vars->dir_x * i) > 0)
	{
		mlx_put_pixel(vars->view_img, vars->p_width_pos + (vars->dir_x * i),
			vars->p_height_pos + (vars->dir_y * i), 0);
		i++;
	}
	olddir_x = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(vars->rotation)
		- vars->dir_y * sin(vars->rotation);
	vars->dir_y = olddir_x * sin(vars->rotation)
		+ vars->dir_y * cos(vars->rotation);
	i = 1;
	while (vars->p_height_pos + (vars->dir_y * i) < vars->m_height * 2
		&& vars->p_height_pos + (vars->dir_y * i) > 0
		&& vars->p_width_pos + (vars->dir_x * i) < vars->m_width * 2
		&& vars->p_width_pos + (vars->dir_x * i) > 0)
	{
		mlx_put_pixel(vars->view_img, vars->p_width_pos + (vars->dir_x * i),
			vars->p_height_pos + (vars->dir_y * i), 255);
		i++;
	}
}

// SKALARPRODUKT
void	rotate_right(t_vars *vars)
{
	int		i;
	double	olddir_x;

	i = 1;
		vars->rotation = 0.0174533;
	while (vars->p_height_pos + (vars->dir_y * i) < vars->m_height * 2
		&& vars->p_height_pos + (vars->dir_y * i) > 0
		&& vars->p_width_pos + (vars->dir_x * i) < vars->m_width * 2
		&& vars->p_width_pos + (vars->dir_x * i) > 0)
	{
		mlx_put_pixel(vars->view_img, vars->p_width_pos + (vars->dir_x * i),
			vars->p_height_pos + (vars->dir_y * i), 0);
		i++;
	}
	olddir_x = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(vars->rotation)
		- vars->dir_y * sin(vars->rotation);
	vars->dir_y = olddir_x * sin(vars->rotation)
		+ vars->dir_y * cos(vars->rotation);
	i = 1;
	while (vars->p_height_pos + (vars->dir_y * i) < vars->m_height * 2
		&& vars->p_height_pos + (vars->dir_y * i) > 0
		&& vars->p_width_pos + (vars->dir_x * i) < vars->m_width * 2
		&& vars->p_width_pos + (vars->dir_x * i) > 0)
{
		mlx_put_pixel(vars->view_img, vars->p_width_pos + (vars->dir_x * i),
			vars->p_height_pos + (vars->dir_y * i), 255);
		i++;
	}
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
		rotate_right(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars);
}
