#include "../../includes/cub3d.h"

void	get_map(t_map *map)
{
	parse_text_and_color(map);
	countinglines(map);
	getmap_content(map);
	map_pars(map);
}
