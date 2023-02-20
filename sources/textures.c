#include "../includes/cub3d.h"

void	delete_txt(t_vars *vars, int alloc_txt)
{
	int	i;

	i = 0;
	while (i < alloc_txt)
		mlx_delete_texture(vars->textures[i]);
}

void	init_textures(t_vars *vars, t_map *map)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		vars->textures[i] = mlx_load_png(map->text_path[i]);
		if (vars->textures[i] == NULL)
		{
			delete_txt(vars, i);
			error_exit("Please check the initialization of your textures!\n");
		}
		i++;
	}
}
