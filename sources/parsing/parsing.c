#include "../../includes/cub3d.h"

int	check_color_comb(char *line)
{
	char	**array;
	int		i;
	int		nbr;

	i = 0;
	check_comma(line);
	array = ft_split(line, ',');
	if (!array)
		error_exit("Error\nAllocation fail");
	if (size_2d_array(array) != 3)
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
	if (!ft_strncmp(line, "NO", 2) && !map->text_path[0])
		map->text_path[0] = ft_strtrim((line + 2), "\t \n");
	else if (!ft_strncmp(line, "SO", 2) && !map->text_path[1])
		map->text_path[1] = ft_strtrim((line + 2), "\t \n");
	else if (!ft_strncmp(line, "WE", 2) && !map->text_path[2])
		map->text_path[2] = ft_strtrim((line + 2), "\t \n");
	else if (!ft_strncmp(line, "EA", 2) && !map->text_path[3])
		map->text_path[3] = ft_strtrim((line + 2), "\t \n");
	else if (!ft_strncmp(line, "F", 1) && !map->rgb_f)
		map->rgb_f = ft_strtrim((line + 1), "\t ");
	else if (!ft_strncmp(line, "C", 1) && !map->rgb_c)
		map->rgb_c = ft_strtrim((line + 1), "\t ");
	else
		error_exit("Error\nDuplicate info : check input file");
}

int	check_identifier(t_map *map)
{
	int	i;

	i = 0;
	while (map->line[i] != '\n')
	{
		if ((map->line[i] >= '\t' && map->line[i] <= '\r') || (map->line[i] == ' '))
			i++;
		else if ((!ft_strncmp(map->line + i, "NO", 2))
			|| (!ft_strncmp(map->line + i, "SO", 2))
			|| (!ft_strncmp(map->line + i, "WE", 2))
			|| (!ft_strncmp(map->line + i, "EA", 2)))
			return (i);
		else if ((!ft_strncmp(map->line + i, "F", 1) && !map->rgb_f)
			|| (!ft_strncmp(map->line + i, "C", 1) && !map->rgb_c))
			return (check_range_colors(map->line + i + 1, i));
		else if ((map->line[i] == '1' || map->line[i] == '0') && map->text_path[0]
			&& map->text_path[1] && map->text_path[2] && map->text_path[3]
			&& map->rgb_f && map->rgb_c)
			return (-1);
		else
			error_exit("Error\nMissing info or wrong character: check input file");
	}
	return (-2);
}

void texture_and_colors_pars(t_map *map)
{
	int		i;

	i = 0;
	map->mapstart = 0;
	while (1)
	{
		map->line = get_next_line(map->fd);
		if (!map->line)
			error_exit("Error\nInfos missing : check input file");
		i = check_identifier(map);
		if (i >= 0)
			fill_var(map->line + i, map);
		else if (i == -1)
			return ;
		free(map->line);
		map->mapstart++;
	}
}
