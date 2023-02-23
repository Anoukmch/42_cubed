#include "../includes/cub3d.h"

void	windowresize(int32_t width, int32_t height, void *param)
{
	t_vars	*vars;

	vars = param;
	vars->m_height = height;
	vars->m_width = width;
	mlx_resize_image(vars->image_3d, vars->m_width, vars->m_height);
	vars->mini_w_height = height / 4;
	vars->mini_w_width = width / 4;
	mlx_resize_image(vars->image_2d, vars->mini_w_width, vars->mini_w_height);
	vars->mini_cube_h = vars->mini_w_height / vars->linesofmap;
	vars->mini_cube_w = vars->mini_w_width / vars->longestline;
}

void	walking_directions(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W)
		&& !movement_hit_wall(vars, W))
	{
		vars->player_x += vars->dir_x * 0.2;
		vars->player_y += vars->dir_y * 0.2;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S)
		&& !movement_hit_wall(vars, S))
	{
		vars->player_x -= vars->dir_x * 0.2;
		vars->player_y -= vars->dir_y * 0.2;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D)
		&& !movement_hit_wall(vars, D))
	{
		vars->player_x -= vars->dir_y * 0.2;
		vars->player_y += vars->dir_x * 0.2;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A)
		&& !movement_hit_wall(vars, A))
	{
		vars->player_x += vars->dir_y * 0.2;
		vars->player_y -= vars->dir_x * 0.2;
	}
}

void	open_door(t_vars *vars)
{
	int	x;
	int	y;

	x = (int)(vars->player_x + vars->dir_x);
	y = (int)(vars->player_y + vars->dir_y);
	if (vars->finalmap[y][x] == '2')
		vars->finalmap[y][x] = '0';
}

// Or we can use the mlx_get_mouse_pos

void	hey(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	(void)button;
	(void)action;
	(void)mods;
	(void)param;
	printf("test\n");
}

void	key_hook(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	walking_directions(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotation(vars, "right");
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotation(vars, "left");
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT))
		rotation(vars, "left");
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_RIGHT))
		rotation(vars, "right");
	mlx_mouse_hook(vars->mlx, &hey, &vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_SPACE))
		open_door(vars);
}

// mlx_hook(cub->win.mlx_win, 4, 0, register_mouseclick, cub);
// mlx_hook(cub->win.mlx_win, 5, 0, unregister_mouseclick, cub);

// typedef void (*mlx_mousefunc)(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
// int	unregister_mouseclick(int button, int x, int y, t_cub *cub)
// int	register_mouseclick(int button, int x, int y, t_cub *cub)
