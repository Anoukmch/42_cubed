/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:02:18 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:30:21 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	delete_txt(t_vars *vars, int alloc_txt)
{
	int	i;

	i = 0;
	while (i < alloc_txt)
	{
		mlx_delete_texture(vars->textures[i]);
		i++;
	}
}

void	free_text_img(t_vars *vars)
{
	mlx_delete_texture(vars->textures[0]);
	mlx_delete_texture(vars->textures[1]);
	mlx_delete_texture(vars->textures[2]);
	mlx_delete_texture(vars->textures[3]);
	mlx_delete_image(vars->mlx, vars->image_3d);
}

void	free_struct(t_map *map)
{
	free_array(map->text_path, 0);
	free_array(map->cmap, 0);
	free(map->line);
	free(map->rgb_f);
	free(map->rgb_c);
	close(map->fd);
}
