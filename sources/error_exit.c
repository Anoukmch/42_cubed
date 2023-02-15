/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:17:04 by amechain          #+#    #+#             */
/*   Updated: 2023/02/15 18:17:48 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map *data()
{
	static t_map map;

	return (&map);
}

int	error_exit(char *s)
{
	ft_putstr_fd(s, 2);
	free_struct(data());
	exit(1);
}

