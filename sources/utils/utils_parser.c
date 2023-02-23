/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:03:25 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (0);
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

void	check_first_and_last(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			error_exit("Error\nCheck first and last map line!\n");
		i++;
	}
}
