#include "../../includes/cub3d.h"

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

int	size_2d_array(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (-1);
	while (array[len])
		len++;
	return (len);
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
