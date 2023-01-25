
#include "../includes/cub3d.h"

int	check_texture_path(char *line, int indic) // How is the path formated ? Can it be in another folder ? (like ../../)
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
			return (indic);
		else
			error_exit("Error\nWrong file path : check input file");
	}
	return(error_exit("Error\nNo file path : check input file"));
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
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
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
		error_exit("Error\nColor code : check input file");
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
		error_exit("Error\nAllocation fail");
	if (size_2Darray(array) != 3)
		return (free_array(array, 0));
	while (array[i])
	{
		printf("array : %s\n", array[i]);
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

int	check_range_colors(char *line, int indic)
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
			error_exit("Error\nColor code : check input file");
	}
	return (indic);
}

void	fill_var(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO", 2) && !map->north_path)
		map->north_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "SO", 2) && !map->south_path)
		map->south_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "WE", 2) && !map->west_path)
		map->west_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "EA", 2) && !map->east_path)
		map->east_path = ft_strtrim((line + 2), "\t ");
	else if (!ft_strncmp(line, "F", 1) && !map->rgb_f)
		map->rgb_f = ft_strtrim((line + 1), "\t ");
	else if (!ft_strncmp(line, "C", 1) && !map->rgb_c)
		map->rgb_c = ft_strtrim((line + 1), "\t ");
	else
		error_exit("Error\nDuplicate info : check input file");
}

int	check_identifier(char *line, t_map *map)
{
	int	i;

	i = 0;
	while(line[i] != '\n')
	{
		if ((line[i] >= '\t' && line[i] <= '\r') || (line[i] == ' '))
			i++;
		else if ((!ft_strncmp(line + i, "NO", 2))
			|| (!ft_strncmp(line + i, "SO", 2))
			|| (!ft_strncmp(line + i, "WE", 2))
			|| (!ft_strncmp(line + i, "EA", 2)))
				return(check_texture_path(line + i + 2, i));
		else if ((!ft_strncmp(line + i, "F", 1) && !map->rgb_f)
			|| (!ft_strncmp(line + i, "C", 1) && !map->rgb_c))
			return(check_range_colors(line + i + 1, i));
		else if ((line[i] == '1' || line[i] == '0') && map->north_path
			&& map->south_path && map->east_path && map->rgb_f && map->rgb_c)
			return (-1);
		else
			error_exit("Error\nMissing info or wrong character : check input file");
	}
	return (-2);
}

char	*texture_and_colors_pars(t_map *map) /* Rework this function */
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(map->fd);
		if (!line)
			error_exit("Error\nNo map : check input file");
		i = check_identifier(line, map);
		if (i >= 0)
			fill_var(line + i, map);
		else if (i == -1)
			return (line);
		free(line);
		map->mapstart++;
	}
	return (NULL);
}

void	parsing(t_map *map)
{
	char *line;

	map->mapstart = 0;
	line = texture_and_colors_pars(map);
	get_finalmap(map, line);
}

void	initialize(char *mapfile, t_map **map)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		error_exit("Error\nAllocation fail");
		//error_exit(NULL, "Error\nAllocation fail\n");
	(*map)->fd = open(mapfile, O_RDONLY);
	if ((*map)->fd < 0)
		error_exit("Error\nOpen fail");
	(*map)->north_path = NULL;
	(*map)->south_path = NULL;
	(*map)->west_path = NULL;
	(*map)->east_path = NULL;
	(*map)->rgb_f = NULL;
	(*map)->rgb_c = NULL;
	(*map)->m_argv = mapfile;
	(*map)->player = 0;
}
