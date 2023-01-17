/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:55:21 by amechain          #+#    #+#             */
/*   Updated: 2023/01/16 16:17:56 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(char *mapfile)
{
	int	len;
	int	fd;

	len = ft_strlen(mapfile);
	fd = open(mapfile, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!(mapfile[len - 4] == '.' && mapfile[len - 3] == 'c'
			&& mapfile[len - 2] == 'u' && mapfile[len - 1] == 'b'))
		return (0);
	return (1);
}
