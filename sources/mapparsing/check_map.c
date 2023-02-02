#include "../../includes/cub3d.h"

void	check_invalid_characters(t_map *map, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] != '0' && str[j] != '1' && str[j] != 'N'
			&& str[j] != 'E' && str[j] != 'S' && str[j] != 'W'
			&& str[j] != ' ')
		{
			printf("Map error: Please check the map characters!\n");
			exit(1);
		}
		if (str[j] != '0' && str[j] != '1' && str[j] != ' ')
		{
			map->player++;
		}
		j++;
	}
}

// 1 == open
// 0 == closed
void	check_vertical_characters(char *str, int j, bool *open)
{
	if (*open == true)
	{
		if (str[j] == '1' && (str[j + 1] == ' ' || !str[j + 1]))
			*open = false;
		else if (str[j] != '0' && str[j] != '1' && str[j] != 'N'
			&& str[j] != 'E' && str[j] != 'S' && str[j] != 'W')
		{
			printf("BOOL: %d\n", *open);
			exit(printf("ERROR\n"));
		}
	}
	else if (*open == false)
	{
		if (str[j] == '1' && (!str[j - 1] || str[j - 1] == ' '))
			*open = true;
		else if (str[j] != '1' && str[j] != ' ')
		{
			printf("BOOL: %d\n", *open);
			exit(printf("ERROR\n"));
		}
	}	
}

void	check_vertical_rendering(char *str)
{
	int		j;
	bool	open;

	j = 0;
	open = false;
	while (str[j] == ' ')
		j++;
	if (str[j] != '1')
		exit(printf("ERROR\n"));
	else
		open = true;
	while (str[j])
	{
		check_vertical_characters(str, j, &open);
		j++;
	}
}

void	check_horizontal_spaces(char **str, int i)
{
	int	j;

	j = 0;
	while (str[i][j])
	{
		if (str[i][j] == ' ')
		{
			if ((i > 0 && str[i - 1][j] != '1' && str[i - 1][j] != ' ')
				|| (str[i + 1] && str[i + 1][j] != '1' && str[i + 1][j] != ' '))
				exit(printf("ERROR horizontal\n"));
		}
		j++;
	}
}

void	check_first_and_last(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			exit(printf("ERROR check first adn alst\n"));
		i++;
	}
}

void	map_pars(t_map *map)
{
	int	i;

	i = 0;
	while (map->cmap[i])
	{
		check_invalid_characters(map, map->cmap[i]);
		if (i == 0 || i == map->maplines)
			check_first_and_last(map->cmap[i]);
		else
		{
			check_vertical_rendering(map->cmap[i]);
		}
		check_horizontal_spaces(map->cmap, i);
		i++;
	}
	if (map->player != 1)
	{
		printf("Map error: Please check the map characters!\n");
		exit(1);
	}
}
