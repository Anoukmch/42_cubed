#include "../includes/cub3d.h"

void	paintingcorners(t_vars *vars, int height, int width)
{
	if (height == 0 && width == 0)
		mlx_draw_texture(vars->map_img,
			vars->textures[CORNER_LEFT_UP], width * 32, height * 32);
	else if (height == 0 && width == vars->m_width - 1)
		mlx_draw_texture(vars->map_img,
			vars->textures[CORNER_RIGHT_UP], width * 32, height * 32);
	else if (height == vars->m_height - 1 && width == vars->m_width - 1)
		mlx_draw_texture(vars->map_img,
			vars->textures[CORNER_RIGHT_DOWN], width * 32, height * 32);
	else if (height == vars->m_height - 1 && width == 0)
		mlx_draw_texture(vars->map_img,
			vars->textures[CORNER_LEFT_DOWN], width * 32, height * 32);
}

void	paintingwalls(t_vars *vars, int height, int width)
{	
	if (height == 0 && vars->map[height][width] == '1')
		mlx_draw_texture(vars->map_img,
			vars->textures[WALL_UP], width * 32, height * 32);
	else if (width == 0 && vars->map[height][width] == '1')
		mlx_draw_texture(vars->map_img,
			vars->textures[WALL_LEFT], width * 32, height * 32);
	else if (width == vars->m_width - 1
		&& vars->map[height][width] == '1')
		mlx_draw_texture(vars->map_img,
			vars->textures[WALL_RIGHT], width * 32, height * 32);
	else if (height == vars->m_height - 1
		&& vars->map[height][width] == '1')
		mlx_draw_texture(vars->map_img,
			vars->textures[WALL_DOWN], width * 32, height * 32);
	else if (vars->map[height][width] == '1')
		mlx_draw_texture(vars->map_img,
			vars->textures[BOX], width * 32, height * 32);
}

void	paintingmap(t_vars *vars)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (height < vars->m_height)
	{
		while (width < vars->m_width)
		{
			mlx_draw_texture(vars->bg_img,
				vars->textures[SPACES], width * 32, height * 32);
			paintingwalls(vars, height, width);
			paintingcorners(vars, height, width);
			if (vars->map[height][width] == 'E')
				mlx_draw_texture(vars->map_img, vars->textures[EXIT],
					width * 32, height * 32);
			if (vars->map[height][width] == 'C')
				mlx_draw_texture(vars->map_img,
					vars->textures[COLLECTS], width * 32, height * 32);
			width++;
		}
		height++;
		width = 0;
	}
}
