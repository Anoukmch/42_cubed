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

int free_text(t_map	*map)
{
	mlx_delete_texture(map->text_path[0]);
	mlx_delete_texture(map->text_path[1]);
	mlx_delete_texture(map->text_path[2]);
	mlx_delete_texture(map->text_path[3]);
}
