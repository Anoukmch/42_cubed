/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/27 13:22:27 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_lines_after_map(t_map *map, char *gnl)
{
	int	i;

	while (gnl)
	{
		i = 0;
		free(gnl);
		gnl = get_next_line(map->fd);
		if (!gnl)
			break ;
		while (gnl[i] == ' ')
			i++;
		if (gnl[i] != '\n' && gnl[i] != '\0')
		{
			free(gnl);
			error_exit("Error\nDelete lines after map!\n");
		}
	}
}

void	countinglines(t_map *map)
{
	char	*gnl;
	int		i;

	while (1)
	{
		i = 0;
		gnl = get_next_line(map->fd);
		if (!gnl)
			break ;
		while (gnl[i] == ' ' || gnl[i] == '\t')
			i++;
		if (gnl[i] == '\n' || gnl[i] == '\0')
			break ;
		if (gnl[i] != '0' && gnl[i] != '1' && gnl[i] != 'N' && gnl[i] != 'E'
			&& gnl[i] != 'S' && gnl[i] != 'W' && gnl[i] != '2')
		{
			free(gnl);
			error_exit("Error\nInvalid map characters!\n");
		}
		free (gnl);
		map->maplines++;
	}
	if (gnl)
		check_lines_after_map(map, gnl);
	close(map->fd);
}

void	getmap_content(t_map *map)
{
	int		count;
	int		read;
	char	*tmp;

	count = 0;
	read = open(map->m_argv, O_RDONLY);
	if (read == -1)
		error_exit("Error\nReading map is impossible!\n");
	while (count < map->mapstart)
	{
		tmp = get_next_line(read);
		free (tmp);
		count++;
	}
	count = 0;
	while (count <= map->maplines)
	{
		tmp = get_next_line(read);
		map->cmap[count] = ft_strtrim(tmp, "\n");
		free (tmp);
		count++;
	}
	close (read);
	map->cmap[count] = NULL;
}

		// if (ft_strchr(tmp, '\n'))
		// 	map->cmap[count] = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		// else
		// 	map->cmap[count] = ft_substr(tmp, 0, ft_strlen(tmp));