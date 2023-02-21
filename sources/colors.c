#include "../includes/cub3d.h"

// uint32_t	get_colour(char *s)
// {
// 	int			i;
// 	int			j;
// 	int			rgb[3];

// 	j = 0;
// 	i = 0;
// 	ft_bzero(rgb, 3);
// 	while (s[i])
// 	{
// 		if (ft_isdigit(s[i]))
// 		{
// 			rgb[j++] = ft_atoi(s + i);
// 			while (s[i] && ft_isdigit(s[i]))
// 				i++;
// 		}
// 		i++;
// 	}
// 	return ((uint32_t)(rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255));
// }

uint32_t get_colour(char *s)
{
	uint32_t finalcolor;
    int rgb[3];
    int i = 0;
    int j = 0;

	ft_memset(rgb, 0, sizeof(rgb));
    while (s && s[i])
    {
        if (ft_isdigit(s[i]))
        {
            rgb[j] = ft_atoi(&s[i]);
			j++;
            while (s[i] && ft_isdigit(s[i]))
				i++;
        }
        i++;
    }
	finalcolor = rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2] + 0xff000000;
    return (finalcolor);
}


void	transform_colors(t_vars *vars, t_map *map)
{
	vars->ceilingcolor = get_colour(map->rgb_c);
	vars->floorcolor = get_colour(map->rgb_f);
}
