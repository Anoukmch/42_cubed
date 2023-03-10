/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:03:35 by jmatheis          #+#    #+#             */
/*   Updated: 2023/02/23 17:04:17 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	character_found(t_vars *vars, char **map, int width, int height)
{
	int			i;
	int			j;
	uint32_t	color;

	i = 0;
	j = 0;
	color = RGB_GREEN;
	if (map[height][width] == '1' || map[height][width] == '2')
	{
		if (map[height][width] == '2')
			color = RGB_BROWN;
		while (i < vars->mini_cube_w)
		{
			while (j < vars->mini_cube_h)
			{
				mlx_put_pixel(vars->image_2d, (width * vars->mini_cube_w + i),
					(height * vars->mini_cube_h + j), color);
				j++;
			}
			j = 0;
			i++;
		}
	}
}

void	draw_player_minimap(t_vars *vars)
{
	int	width;
	int	height;

	width = (vars->mini_cube_w / 4) * -1;
	height = (vars->mini_cube_h / 4) * -1;
	while (width < vars->mini_cube_w / 4)
	{
		while (height < vars->mini_cube_h / 4)
		{
			mlx_put_pixel(vars->image_2d,
				vars->player_x * vars->mini_cube_w + width,
				vars->player_y * vars->mini_cube_h + height, RGB_BLUE);
			height++;
		}
		height = (vars->mini_cube_h / 4) * -1;
		width++;
	}
}

void	draw_minimap(t_vars *vars, char **map)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (map[height])
	{
		while (map[height][width])
		{
			character_found(vars, map, width, height);
			width++;
		}
		height++;
		width = 0;
	}
	draw_player_minimap(vars);
}

void	init_minimap(t_vars *vars)
{
	vars->mini_w_height = vars->w_height / 4;
	vars->mini_w_width = vars->w_width / 4;
	vars->mini_cube_h = vars->mini_w_height / vars->linesofmap;
	vars->mini_cube_w = vars->mini_w_width / vars->longestline;
}

void	draw_rays_minimap(t_cast *t, t_vars *vars, uint32_t color)
{
	int	i;

	i = 0;
	while (i < vars->mini_cube_w)
	{
		mlx_put_pixel(vars->image_2d, \
			(vars->player_x * vars->mini_cube_w) + (t->raydir_x * i),
			vars->player_y * vars->mini_cube_h + (t->raydir_y * i), color);
		i++;
	}
}

// AT THE END OF DDA:
// mlx_image_to_window(vars->mlx, vars->rays, 0, 0);
