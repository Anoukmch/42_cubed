/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:17:53 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/01 12:39:47 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

typedef struct s_vars
{
	double w;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int		mapX;
	int		mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double stepX;
	double stepY;
	int hit;
	int side;
	int i;

}				t_vars;

static void	set_ray(int x, t_vars *cub)
{
	cub->w = 1000;
	cub->cameraX = (double)((2 * x) / (double)cub->w - 1);
	cub->ray_dir.x = cub->dir.x + (cub->plane.x * cub->camera);
	cub->ray_dir.y = cub->dir.y + (cub->plane.y * cub->camera);
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->map.x = ray->pos.x;
	ray->map.y = ray->pos.y;
}

static void	calculate_ray_distance(t_ray *ray)
{
	ray->hit = 0;
	ray->step.x = 1;
	ray->side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	ray->step.y = 1;
	ray->side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist.y;
	}
}

/*
 * dda() helper to comply w/ norm
 * sets ray->side and ray->wall_distance
 */
void	set_ray_side_and_w_distance(t_ray *ray, int is_x_side, int is_negative)
{
	if (is_x_side)
	{
		if (is_negative)
			ray->side = NO;
		else
			ray->side = SO;
	}
	else
	{
		if (is_negative)
			ray->side = EA;
		else
			ray->side = WE;
	}
	if (is_x_side)
		ray->wall_distance = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->wall_distance = ray->side_dist.y - ray->delta_dist.y;
}

/*
 * Digital Differential Analysis
 * wall_distance = perpWallDist;
 */
static void	dda(t_cub *cub, t_ray *ray)
{
	int	is_x_side;
	int	is_negative;

	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			is_x_side = 1;
			is_negative = ray->ray_dir.x < 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			is_x_side = 0;
			is_negative = ray->ray_dir.y < 0;
		}
		if (cub->d->map[ray->map.x][ray->map.y] > '0')
			ray->hit = 1;
	}
	set_ray_side_and_w_distance(ray, is_x_side, is_negative);
}

void	render_ray(void)
{
	int		i;

	i = 0;
	t_vars *cub = malloc(sizeof(t_vars) * 1);
	double w = 1000;
	while (i < w)
	{
		set_ray(i, cub);
		calculate_ray_distance(cub->ray);
		dda(cub, cub->ray);
		draw_ray(i, cub, cub->ray);
		i++;
	}
}
