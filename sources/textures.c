#include "../includes/cub3d.h"

void	init_textures(t_vars *vars, t_map *map)
{
	int	i;
	i = 0;

	while (i < TEXTURES)
	{
		vars->textures[i] = mlx_load_png(map->text_path[i]);
		if (vars->textures[i] == NULL)
			exit(printf("Please check the initialization of your textures!\n"));
		i++;
	}
}
