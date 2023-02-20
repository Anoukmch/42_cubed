#include "../../includes/cub3d.h"

void	get_finalmap(t_map *map)
{
	countinglines(map);
	getmap_content(map);
	map_pars(map);
}
