#include "../includes/cub3d.h"

void	playerright(t_vars *vars)
{
	int	w;
	int	h;

	w = vars->p_width;
	h = vars->p_height;
	if (vars->map[h][w + 1] != '1' && (vars->map[h][w + 1] != 'E'
			|| vars->coll_no == vars->coll_counter))
	{
		vars->player_img->instances[0].x += 32;
		vars->p_width = w + 1;
		vars->p_height = h;
		exit_and_collectible(vars);
	}
}

void	playerleft(t_vars *vars)
{
	int	w;
	int	h;

	w = vars->p_width;
	h = vars->p_height;
	if (vars->map[h][w - 1] != '1' && (vars->map[h][w - 1] != 'E'
			|| vars->coll_no == vars->coll_counter))
	{
		vars->player_img->instances[0].x -= 32;
		vars->p_width = w - 1;
		vars->p_height = h;
		exit_and_collectible(vars);
	}
}

void	playerup(t_vars *vars)
{
	int	w;
	int	h;

	w = vars->p_width;
	h = vars->p_height;
	if (vars->map[h - 1][w] != '1' && (vars->map[h - 1][w] != 'E'
			|| vars->coll_no == vars->coll_counter))
	{
		vars->player_img->instances[0].y -= 32;
		vars->p_width = w;
		vars->p_height = h - 1;
		exit_and_collectible(vars);
	}
}

void	playerdown(t_vars *vars)
{
	int	w;
	int	h;

	w = vars->p_width;
	h = vars->p_height;
	if (vars->map[h + 1][w] != '1' && (vars->map[h + 1][w] != 'E'
			|| vars->coll_no == vars->coll_counter))
	{
		vars->player_img->instances[0].y += 32;
		vars->p_width = w;
		vars->p_height = h + 1;
		exit_and_collectible(vars);
	}
}

void	exit_and_collectible(t_vars *vars)
{
	if (vars->map[vars->p_height][vars->p_width] == 'E')
	{
		vars->steps++;
		mlx_close_window(vars->mlx);
		ft_printf("\nCongrats, you won with %i steps!\n\n", vars->steps);
		exit_and_free(vars, 0);
	}
	if (vars->map[vars->p_height][vars->p_width] == 'C')
	{
		vars->coll_counter++;
		mlx_draw_texture(vars->map_img, vars->textures[SPACES],
			vars->p_width * 32, vars->p_height * 32);
		vars->map[vars->p_height][vars->p_width] = '0';
	}
	vars->steps++;
	ft_printf("step: %d\n", vars->steps);
}
