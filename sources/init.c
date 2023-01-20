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

void	view_starting_direction(t_vars *vars)
{
	int	i;

	i = 1;
	// CHANGE VECTORS TO START IN ANOTHER DIRECTION
	vars->dir_x = 0;
	vars->dir_y = -1;
	vars->view_img = mlx_new_image(vars->mlx,
			vars->m_width * 2, vars->m_height * 2);
	while (vars->p_height_pos + (vars->dir_y * i) < vars->m_height * 2
		&& vars->p_height_pos + (vars->dir_y * i) > 0
		&& vars->p_width_pos + (vars->dir_x * i) < vars->m_width * 2
		&& vars->p_width_pos + (vars->dir_x * i) > 0)
	{
		mlx_put_pixel(vars->view_img, vars->p_width_pos + (vars->dir_x * i),
			vars->p_height_pos + (vars->dir_y * i), 255);
		i++;
	}
	mlx_image_to_window(vars->mlx, vars->view_img, 0, 0);
}
