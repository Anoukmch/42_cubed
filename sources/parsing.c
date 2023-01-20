/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:07:31 by amechain          #+#    #+#             */
/*   Updated: 2023/01/20 08:36:12 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_texture_path(char *line) // How is the path formated ? Can it be in another folder ? (like ../../)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == '\t' || line[i] == ' ')
			i++;
		else if (line[i] == '.' && line[i + 1] == '/' && line[i + 2]
			&& line[i + 2] >= 33 && line[i + 2] <= 126
			&& line[i + 2] != '.' && line[i + 2] != '/' && line[i + 2] != '\\')
			return ;
		else
		{
			printf("Error\nPlease check file path\n");
			exit(1);
		}
			//error_exit(NULL, "Error\nPlease check file path\n");
	}
	printf("Error\nPlease add a path\n");
	exit(1);
}

int	size_2Darray(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (-1);
	while (array[len])
		len++;
	return (len);
}

int	isdigit_string(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
			return (0); // not a digit
		i++;
	}
	return (1);
}

void	check_comma(char *line)
{
	int	i;
	int	comma_nbr;

	i = 0;
	comma_nbr = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma_nbr++;
		i++;
	}
	if (comma_nbr != 2)
	{
		printf("Error\nPlease check color code\n");
		exit(1);
	}

}

int	free_array(char **array, int ret_stat)
{
	int	i;

	i = 0;
	if (!array)
		return (ret_stat);
	while (array[i])
		free(array[i++]);
	free(array);
	return (ret_stat);
}

int	check_color_comb(char *line)
{
	char **array;
	int	i;
	int nbr;

	i = 0;
	check_comma(line);
	array = ft_split(line, ',');
	if (!array)
	{
		printf("Error\nAllocation fail\n");
		exit(1);
	}
	if (size_2Darray(array) != 3)
		return (free_array(array, 0));
	while (array[i])
	{
		if (isdigit_string(array[i]))
		{
			nbr = ft_atoi(array[i]);
			if (nbr < 0 || nbr > 255)
				return (free_array(array, 0));
		}
		else
			return (free_array(array, 0));
		i++;
	}
	return (free_array(array, 1));
}

int	check_range_colors(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == '\t' || line[i] == ' ')
			i++;
		else if (check_color_comb(line + i))
			break ;
		else
		{
			printf("Error\nPlease check color code\n");
			exit(1);
		}
			//error_exit(NULL, "Error\nPlease check color code\n");
	}
	return (0);
}

void	fill_var(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO", 2))
		map->north_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "SO", 2))
		map->south_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "WE", 2))
		map->west_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "EA", 2))
		map->east_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "F", 1))
		map->rgb_f = ft_strtrim((line + 1), "\t ");
	else if (!ft_strncmp(line, "C", 1))
		map->rgb_c = ft_strtrim((line + 1), "\t ");
}

int	check_identifier(char *line, t_map *map)
{
	int	i;

	i = 0;
	while(line[i] != '\n')
	{
		if ((line[i] >= '\t' && line[i] <= '\r') || (line[i] == ' '))
			i++;
		else if ((!ft_strncmp(line + i, "NO", 2) && !map->north_path)
			|| (!ft_strncmp(line + i, "SO", 2) && !map->south_path)
			|| (!ft_strncmp(line + i, "WE", 2) && !map->west_path)
			|| (!ft_strncmp(line + i, "EA", 2) && !map->east_path))
		{
			check_texture_path(line + i + 2);
			return (i);
		}
		else if ((!ft_strncmp(line + i, "F", 1) && !map->rgb_f)
			|| (!ft_strncmp(line + i, "C", 1) && !map->rgb_c))
		{
			check_range_colors(line + i + 1);
			return (i);
		}
		else
		{
			printf("Error\nPlease check input file\n");
			exit(1);
		}
			//error_exit(NULL, "Error\nPlease check identifier\n");
	}
	return (-1);
}

char	*texture_and_colors_pars(t_map *map) /* Rework this function */
{
	char	*line;
	int		i;

	i = 0;
	map->mapstart = 0;
	line = get_next_line(map->fd);
	if (!line)
	{
		printf("Error\nGet next line fail\n");
		exit(1);
	}
	while (!map->north_path || !map->south_path || !map->west_path
		|| !map->east_path || !map->rgb_f || !map->rgb_c)
	{
		i = check_identifier(line, map);
		if (i >= 0)
			fill_var(line + i, map);
		free(line);
		line = get_next_line(map->fd);
		map->mapstart++;
	}
	printf("north_path :%s\n", map->north_path);
	printf("south_path :%s\n", map->south_path);
	printf("east_path :%s\n", map->east_path);
	printf("west_path :%s\n", map->west_path);
	printf("rgb_f :%s\n", map->rgb_f);
	printf("rgb_c :%s\n", map->rgb_c);
	return (line);
}

void	parsing(t_map *map)
{
	char *line;

	line = texture_and_colors_pars(map);
	get_finalmap(map, line);
}

void	initialize(char *mapfile, t_map **map)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
	{
		printf("Error\nAllocation fail\n");
		exit(1);
	}
		//error_exit(NULL, "Error\nAllocation fail\n");
	(*map)->fd = open(mapfile, O_RDONLY);
	if ((*map)->fd < 0)
	{
		printf("Error\nOpen fail\n");
		exit(1);
	}
	(*map)->north_path = NULL;
	(*map)->south_path = NULL;
	(*map)->west_path = NULL;
	(*map)->east_path = NULL;
	(*map)->rgb_f = NULL;
	(*map)->rgb_c = NULL;
	(*map)->m_argv = mapfile;
	(*map)->player = 0;
}
