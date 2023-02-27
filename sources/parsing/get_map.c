/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/27 13:22:22 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	checktransitionlines(t_map *map)
{
	char	*gnl;
	int		i;

	i = 0;
	gnl = map->line;
	while (1)
	{
		while (gnl[i] == ' ' || gnl[i] == '\t')
			i++;
		if (gnl[i] == '\n')
		{
			map->mapstart++;
			gnl = get_next_line(map->fd);
			i = 0;
		}
		else
			break ;
	}
}

void	get_map(t_map *map)
{
	parse_text_and_color(map);
	checktransitionlines(map);
	countinglines(map);
	if (!map->maplines)
		error_exit("Error\nNo existing map!\n");
	map->cmap = ft_calloc((map->maplines + 2), sizeof(char *));
	if (!map->cmap)
		error_exit("Error\nAllocation error\n");
	getmap_content(map);
	map_pars(map);
}
