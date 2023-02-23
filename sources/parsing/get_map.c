/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:03:02 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_map(t_map *map)
{
	parse_text_and_color(map);
	countinglines(map);
	getmap_content(map);
	map_pars(map);
}
