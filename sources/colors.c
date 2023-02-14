#include "../includes/cub3d.h"

uint32_t	get_colour(char *s)
{
	int			i;
	int			j;
	int			rgb[3];

	j = 0;
	i = 0;
	ft_bzero(rgb, 3);
	while (s[i])
	{
		if (ft_isdigit(s[i]))
		{
			rgb[j++] = ft_atoi(s + i);
			while (s[i] && ft_isdigit(s[i]))
				i++;
		}
		i++;
	}
	return ((uint32_t)(rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255));
}

void	transform_colors(t_vars *vars, t_map *map)
{
	vars->ceilingcolor = get_colour(map->rgb_c);
	printf("ceiling: %d\n", vars->ceilingcolor);
	vars->floorcolor = get_colour(map->rgb_f);
}
