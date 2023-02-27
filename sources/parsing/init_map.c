/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:03:04 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_map(char *mapfile, t_map *map)
{
	map->maplines = 0;
	map->line = NULL;
	map->rgb_f = NULL;
	map->rgb_c = NULL;
	map->cmap = NULL;
	map->text_path = NULL;
	map->fd = open(mapfile, O_RDONLY);
	if (map->fd < 0)
		error_exit("Error\nOpen fail\n");
	map->text_path = ft_calloc(5, sizeof (char *));
	if (!map->text_path)
		error_exit("Error\nAllocation fail\n");
	map->m_argv = mapfile;
	map->player = 0;
	map->maplines = 0;
	map->mapstart = 0;
}
