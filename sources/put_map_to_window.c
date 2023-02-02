#include "../includes/cub3d.h"

void	init_textures(t_vars *vars)
{
	vars->textures[WALL] = mlx_load_png("./sources/pngfiles/walls.png");
	if (!vars->textures[WALL])
		exit(printf("Check init of textures\n"));
	if (vars->textures[WALL]->height != 32 || vars->textures[WALL]->width != 32)
		exit(printf("Check size of textures\n"));
}

void	paintingmap(t_map *map)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (map->cmap[height])
	{
		while (map->cmap[height][width])
		{
			if (map->cmap[height][width] == 'N' || map->cmap[height][width] == 'E'
				|| map->cmap[height][width] == 'S' || map->cmap[height][width] == 'W')
			{
				// vars->player_x = width;
				// vars->player_y = height;
			}
			if (map->cmap[height][width] == '1')
			{
				// mlx_draw_texture(vars->map_img, vars->textures[WALL],
				// 	width * 32, height * 32);
			}
			width++;
		}
		height++;
		width = 0;
	}
}

void	init_map(t_vars *vars, t_map *map)
{
	// vars->map_img = mlx_new_image(vars->mlx,
	// 	vars->m_width * 32, vars->m_height * 32);
	init_textures(vars);
	paintingmap(map);
	// mlx_image_to_window(vars->mlx, vars->map_img, 0, 0);
}