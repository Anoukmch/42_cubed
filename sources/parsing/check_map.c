/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/25 14:16:54 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_first_and_lastline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			error_exit("Error\nCheck first and last map line!\n");
		i++;
	}
}

void	check_invalid_characters(t_map *map, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] != '0' && str[j] != '1' && str[j] != 'N'
			&& str[j] != 'E' && str[j] != 'S' && str[j] != 'W'
			&& str[j] != ' ' && str[j] != '2')
			error_exit("Error\nPlease check the map characters!\n");
		if (str[j] != '0' && str[j] != '1' && str[j] != ' ' && str[j] != '2')
			map->player++;
		j++;
	}
}

void	check_vertical_rendering(char *str)
{
	int		j;

	j = 0;
	while (str[j] == ' ')
		j++;
	if (str[j] != '1')
		error_exit("Error\n first char not a wall!\n");
	while (str[j])
	{
		if ((str[j] == '0' || str[j] == '2' || str[j] == 'W'
			|| str[j] == 'N' || str[j] == 'S' || str[j] == 'E')
			&& (!str[j + 1] || (str[j + 1] && str[j + 1] == ' ')))
			error_exit("Error\nvertical mistake!\n");
		else if (str[j] == ' ' && str[j + 1]
			&& str[j + 1] != ' ' && str[j + 1] != '1')
			error_exit("Error\nvertical mistake!\n");
		j++;
	}
}

void	check_horizontal_rendering(char **str, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i][j])
	{
		if (str[i][j] == ' ')
		{
			if ((i > 0 && (int)ft_strlen(str[i - 1]) > j
					&& str[i - 1][j] != '1' && str[i - 1][j] != ' ')
				|| (str[i + 1] && (int)ft_strlen(str[i + 1]) > j
					&& str[i + 1][j] != '1' && str[i + 1][j] != ' '))
				error_exit("Error\nHORIZONTAL CHECK!\n");
		}
		if (((i > 0 && (int)ft_strlen(str[i - 1]) <= j)
			|| (str[i + 1] && (int)ft_strlen(str[i + 1]) <= j))
			&& str[i][j] != '1' && str[i][j] != ' ')
			error_exit("Error\nHORIZONTAL CHECK!\n");
		j++;
	}
}

void	map_pars(t_map *map)
{
	int	i;

	i = 0;
	while (map->cmap[i])
	{
		check_invalid_characters(map, map->cmap[i]);
		if (i == 0 || i == map->maplines)
			check_first_and_lastline(map->cmap[i]);
		else
			check_vertical_rendering(map->cmap[i]);
		check_horizontal_rendering(map->cmap, i);
		check_doors(map->cmap, i);
		i++;
	}
	if (map->player != 1)
		error_exit("Error\nPlease check the map characters!\n");
}
