#include "../includes/cub3d.h"

void	exit_and_free(t_vars *vars, int status)
{
	int	h;

	h = 0;
	while (h < vars->m_height && vars->map[h])
	{
		free(vars->map[h]);
		h++;
	}
	free(vars->map);
	h = 0;
	while (h < TEXTURES)
	{
		if (vars->textures[h])
			mlx_delete_texture(vars->textures[h]);
		h++;
	}	
	if (vars->mlx)
		mlx_terminate(vars->mlx);
	exit (status);
}

void	counting_character(t_vars *vars, int w, int h)
{
	if (vars->map[h][w] == 'C')
		vars->coll_no++;
	if (vars->map[h][w] == 'P')
		vars->player_no++;
	if (vars->map[h][w] == 'E')
		vars->exit_no++;
}

void	errorhandling(t_vars *vars, int w, int h)
{
	counting_character(vars, w, h);
	if (vars->map[h][w] != '0' &&
		vars->map[h][w] != 'C' && vars->map[h][w] != 'E' &&
		vars->map[h][w] != 'P' && vars->map[h][w] != '1')
	{
		ft_printf("Map error: Please check the map characters!\n");
		exit_and_free(vars, 1);
	}
	if (vars->map[0][w] != '1' ||
		vars->map[vars->m_height - 1][w] != '1' ||
		vars->map[h][0] != '1' ||
		vars->map[h][vars->m_width - 1] != '1')
	{
		ft_printf("Map error: Please surround your map with walls!\n");
		exit_and_free(vars, 1);
	}
}

void	rectangle_check(t_vars *vars)
{
	int	firstline;
	int	h;

	firstline = (int)ft_strlen(vars->map[0]);
	h = 1;
	while (h < vars->m_height - 1)
	{
		if ((int)ft_strlen(vars->map[h]) != firstline)
		{
			ft_printf("Map error: Please check the length of your lines!\n");
			exit_and_free(vars, 1);
		}
		h++;
	}
	if (firstline != (int)ft_strlen(vars->map[vars->m_height - 1]) + 1)
	{
		ft_printf("Map error: Please check the length of your lines!\n");
		exit_and_free(vars, 1);
	}
}
