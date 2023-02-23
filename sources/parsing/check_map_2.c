/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:02:52 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_doors(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == '2' && (map[i][j - 1] != '1' || map[i][j + 1] != '1')
			&& (map[i - 1][j] != '1' || map[i + 1][j] != '1'))
			error_exit("Error\nDoors must be surrounded by walls\n");
		j++;
	}
}
