/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:03:11 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_free_strtrim(char *s1, char const *set)
{
	size_t	len;
	char	*final;

	if (set == 0 || s1 == 0)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[len]))
		len--;
	final = ft_substr(s1, 0, len + 1);
	free (s1);
	return (final);
}

void	checkemptylines(t_map *map)
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

void	check_lines_after_map(t_map *map, char *gnl)
{
	int	i;

	while (gnl)
	{
		free(gnl);
		gnl = get_next_line(map->fd);
		i = 0;
		while (gnl && gnl[i] == ' ')
			i++;
		if (ft_strcmp(&gnl[i], "\n") && gnl && ft_strcmp(&gnl[i], "\0"))
		{
			free(gnl);
			error_exit("Error\nDelete lines after map!\n");
		}
	}
}

void	countinglines(t_map *map)
{
	char	*gnl;

	checkemptylines(map);
	while (1)
	{
		gnl = get_next_line(map->fd);
		if (!ft_strcmp(gnl, "\n"))
			break ;
		if (gnl == NULL)
			break ;
		free (gnl);
		map->maplines++;
	}
	check_lines_after_map(map, gnl);
	close(map->fd);
	if (!map->maplines)
	{
		free(gnl);
		error_exit("Error\nNo existing map!\n");
	}
}

void	getmap_content(t_map *map)
{
	int		count;
	int		read;
	char	*tmp;

	count = 0;
	map->cmap = ft_calloc((map->maplines + 2), sizeof(char *));
	if (!map->cmap)
		error_exit("Error\nAllocation error\n");
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
	while (count < map->maplines + 1)
	{
		map->cmap[count] = ft_free_strtrim(get_next_line(read), "\n");
		count++;
	}
	map->cmap[count] = NULL;
	close (read);
}
