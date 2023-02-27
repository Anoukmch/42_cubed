/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:03:35 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:09:09 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// convert floor & ceiling color to a 32-bit ARGB color
// << 24 --> red value shifted to left by 24 bits
// << 24 = multiplying no. with * 256 * 256
// << 16 --> green value shifted to left by 16 bits
// << 16 = multiplying no. with * 256
// << 8 --> blue value shifted to left by 8 bits
// << 8 = multiplying with nothing
// << 255 represents value of 0xFF (max val for the alpha component needed)
// AARRGGBB (AA = alpha component value)
uint32_t	get_color(char *s)
{
	uint32_t	finalcolor;
	int			rgb[3];
	int			iter;
	int			col;

	iter = 0;
	col = 0;
	ft_memset(rgb, 0, sizeof(rgb));
	while (s && s[iter])
	{
		if (ft_isdigit(s[iter]))
		{
			rgb[col] = ft_atoi(&s[iter]);
			col++;
			while (s[iter] && ft_isdigit(s[iter]))
				iter++;
		}
		iter++;
	}
	finalcolor = (uint32_t)((rgb[0] << 24) + (rgb[1] << 16) \
		+ (rgb[2] << 8) + 255);
	return (finalcolor);
}

void	transform_colors(t_vars *vars, t_map *map)
{
	vars->ceilingcolor = get_color(map->rgb_c);
	vars->floorcolor = get_color(map->rgb_f);
}
