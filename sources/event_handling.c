#include "../includes/cub3d.h"

void	windowresize(int32_t width, int32_t height, void *param)
{
	t_vars	*vars;

	vars = param;
	vars->m_height = height;
	vars->m_width = width;
	mlx_resize_image(vars->image_3d, vars->m_width, vars->m_height);
}

void	walking_directions(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W)
		&& !movement_hit_wall(vars, NO))
	{
		vars->player_x += vars->dir_x * 0.1;
		vars->player_y += vars->dir_y * 0.1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S)
		&& !movement_hit_wall(vars, SO))
	{
		vars->player_x -= vars->dir_x * 0.1;
		vars->player_y -= vars->dir_y * 0.1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D)
		&& !movement_hit_wall(vars, EA))
	{
		vars->player_x -= vars->dir_y * 0.1;
		vars->player_y += vars->dir_x * 0.1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A)
		&& !movement_hit_wall(vars, WE))
	{
		vars->player_x += vars->dir_y * 0.1;
		vars->player_y -= vars->dir_x * 0.1;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
	walking_directions(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotation(vars, "right");
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotation(vars, "left");
}
