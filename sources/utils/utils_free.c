#include "../../includes/cub3d.h"

int	free_array(char **array, int ret_stat)
{
	int	i;

	i = 0;
	if (!array)
		return (ret_stat);
	while (array[i])
		free(array[i++]);
	free(array);
	return (ret_stat);
}

void free_text_img(t_vars *vars)
{
	mlx_delete_texture(vars->textures[0]);
	mlx_delete_texture(vars->textures[1]);
	mlx_delete_texture(vars->textures[2]);
	mlx_delete_texture(vars->textures[3]);
	mlx_delete_image(vars->mlx, vars->image_3d);
}

void free_struct(t_map *map)
{
	free_array(map->text_path, 0);
	free_array(map->cmap, 0);
	free(map->line);
	free(map->rgb_f);
	free(map->rgb_c);
	close(map->fd); // can we close a fd < 0 ?
}

