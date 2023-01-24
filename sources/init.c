#include "../includes/cub3d.h"

void	init_window(t_vars *vars)
{
	vars->m_width = 30 * 32;
	vars->m_height = 30 * 32;
	vars->mlx = mlx_init(vars->m_width, vars->m_height, "MLX42", true); //opening a window
	if (!vars->mlx)
		exit(EXIT_FAILURE);
}

void	init_player(t_vars *vars)
{
	vars->p_width_pos = 128;
	vars->p_height_pos = 128;
	vars->player_img = mlx_new_image(vars->mlx, 1, 1); //Change size of cube here
	ft_memset(vars->player_img->pixels, 255,
		vars->player_img->width * vars->player_img->height * sizeof(int));
	mlx_image_to_window(vars->mlx, vars->player_img,
		vars->p_width_pos, vars->p_height_pos); //position in pixel/in window
}

void sidesofview(t_vars *vars)
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

void	view_starting_direction(t_vars *vars)
{
	int	i;

	i = 1;
	vars->fov = 1.15192; //66 degree in radiant
	// CHANGE VECTORS TO START IN ANOTHER DIRECTION
	vars->dir_x = 0;
	vars->dir_y = -1;
	// EAST
	// vars->dir_x = 1;
	// vars->dir_y = 0;
	// SOUTH
	// vars->dir_x = 0;
	// vars->dir_y = 1;
	// WEST
	// vars->dir_x = -1;
	// vars->dir_y = 0;
	vars->view_img = mlx_new_image(vars->mlx,
			vars->m_width * 2, vars->m_height * 2);
	get_view(vars, 255, vars->dir_x, vars->dir_y);
	// GET SIDES OF FOV
	sidesofview(vars);
	get_view(vars, 255, vars->left_x, vars->left_y);
	get_view(vars, 255, vars->right_x, vars->right_y);

	mlx_image_to_window(vars->mlx, vars->view_img, 0, 0);
	// mlx_put_pixel(vars->view_img, 20, 30, 255);
}
