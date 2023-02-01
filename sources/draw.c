/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:19:57 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/01 12:12:29 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/*
 * comments!
*/
// static int	tex_pos(t_cub *cub)
// {
// 	double	x;
// 	int		tex_x;

// 	if (cub->ray->side == NO || cub->ray->side == SO)
// 		x = cub->ray->pos.y + cub->ray->wall_distance * cub->ray->ray_dir.y;
// 	else
// 		x = cub->ray->pos.x + cub->ray->wall_distance * cub->ray->ray_dir.x;
// 	x -= floor(x);
// 	tex_x = x * cub->d->textures[cub->ray->side]->width;
// 	if ((cub->ray->side == NO && cub->ray->ray_dir.x > 0) \
// 	|| (cub->ray->side == SO && cub->ray->ray_dir.y < 0))
// 		tex_x = cub->d->textures[cub->ray->side]->width - tex_x - 1;
// 	return (tex_x);
// }

// static void	texturize(t_cub *cub, int x, int start, int end)
// {
// 	int				line_h;
// 	double			step;
// 	double			tex_p;
// 	mlx_texture_t	*tex;
// 	int				tmp;

// 	step = 0;
// 	tex = cub->d->textures[cub->ray->side];
// 	line_h = end - start;
// 	start = fmax(0, (cub->s_height - line_h) / 2);
// 	tex_p = (start - (cub->s_height + line_h) / 2) * step;
// 	step = 1.0 * tex->height / line_h;
// 	while (start < end)
// 	{
// 		tmp = (int)tex_p & (tex->height - 1);
// 		tex_p += step;
// 		ft_memcpy(&cub->image->pixels[((start * cub->image->width + x) * 4)], \
// 		&tex->pixels[(tmp * tex->height + tex_pos(cub)) * 4], 4);
// 		start++;
// 	}
// }

void	draw_ray(int x, t_cub *cub, t_ray *ray)
{
	int	line_height;
	int	start;
	int	end;
	int	i;

	line_height = 0;
	if (ray->wall_distance > 0)
		line_height = (int)(cub->s_height / ray->wall_distance);
	start = (cub->s_height - line_height) / 2;
	end = (line_height + cub->s_height) / 2;
	if (end >= cub->s_height)
		end = cub->s_height - 1;
	//texturize(cub, x, start, end);
	i = 0;
	while (i < cub->s_height)
	{
		if (i <= start)
			mlx_put_pixel(cub->image, x, i, cub->c_colour);
		if (i >= end)
			mlx_put_pixel(cub->image, x, i, cub->f_colour);
		i++;
	}
}
