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
