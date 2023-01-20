#include "../../includes/cub3d.h"

// HELPER FUNCTION
void	printmap(t_map *map)
{
	int	i;

	i = 0;
	printf("+++++ MAP +++++\n");
	while (map->cmap[i])
	{
		printf("%s\n", map->cmap[i]);
		i++;
	}
	printf("\n");
}

void	get_finalmap(t_map *map, char *lastline)
{
	countinglines(map, lastline);
	getmap_content(map);
	map_pars(map);
	printmap(map);
}
