#include "../includes/cub3d.h"

#define RGB_BLUE	0xA6C0
#define RGB_WHITE	0xFFFFFFFF
#define RGB_GREEN	0x00996699
#define RGB_YELLOW	0xFFFF007F
#define RGB_PINK	0xFF006699

void	character_found(t_vars *vars, char **map, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (map[height][width] == '1')
	{
		while (i < vars->mini_cube_w)
		{
			while (j < vars->mini_cube_h)
			{
				mlx_put_pixel(vars->image_2d, (width * vars->mini_cube_w + i),
					(height * vars->mini_cube_h + j), RGB_GREEN);
				j++;
			}
			j = 0;
			i++;
		}
	}
}

void	draw_player_minimap(t_vars *vars)
{
	int	width;
	int	height;

	width = (vars->mini_cube_w / 4) * -1;
	height = (vars->mini_cube_h / 4) * -1;
	while (width < vars->mini_cube_w / 4)
	{
		while (height < vars->mini_cube_h / 4)
		{
			mlx_put_pixel(vars->image_2d,
				vars->player_x * vars->mini_cube_w + width,
				vars->player_y * vars->mini_cube_h + height, RGB_BLUE);
			height++;
		}
		height = (vars->mini_cube_h / 4) * -1;
		width++;
	}
}

void	draw_minimap(t_vars *vars, char **map)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (map[height])
	{
		while (map[height][width])
		{
			character_found(vars, map, width, height);
			width++;
		}
		height++;
		width = 0;
	}
	draw_player_minimap(vars);
}

void	init_minimap(t_vars *vars)
{
	vars->mini_w_height = vars->w_height / 4;
	vars->mini_w_width = vars->w_width / 4;
	vars->mini_cube_h = vars->mini_w_height / vars->linesofmap;
	vars->mini_cube_w = vars->mini_w_width / vars->longestline;
}

void	draw_rays_minimap(t_cast *t, t_vars *vars, uint32_t color)
{
	int	i;

	i = 0;
	while (i < vars->mini_cube_w)
	{
		mlx_put_pixel(vars->image_2d, \
			(vars->player_x * vars->mini_cube_w) + (t->raydir_x * i),
			vars->player_y * vars->mini_cube_h + (t->raydir_y * i), color);
		i++;
	}
}

// AT THE END OF DDA:
// mlx_image_to_window(vars->mlx, vars->rays, 0, 0);