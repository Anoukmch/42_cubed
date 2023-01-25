#include <math.h>
#include "../includes/cub3d.h"

void	get_view_wall(t_vars *vars, int color, double x, double y)
{
	int	i;

	i = 1;
	while ((vars->player_y * 32) + 16 + (y * i) < vars->m_height * 32 * 2
		&& (vars->player_y * 32) + 16 + (y * i) > 0
		&& (vars->player_x * 32) + 16 + (x * i) < vars->m_width * 32 * 2
		&& (vars->player_x * 32) + 16 + (x * i) > 0)
	{
		mlx_put_pixel(vars->player_img, (vars->player_x * 32) + 16 + (x * i),
			(vars->player_y * 32) + 16 + (y * i), color);
		i++;
	}
}

void	dda(t_vars *vars)
{
	int x;
	double w;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	int stepX;
	int stepY;
	int hit;
	int side;
	int i;

	x = 0;
	w = 32;
	// while (x < w)
	// {
		i = 0;
		hit = 0;
		side = 0;
		cameraX = 2 * 1 / 32 - 1;
		rayDirX = vars->dir_x + vars->planex * cameraX;
		rayDirY = vars->dir_y + vars->planey * cameraX;
		printf("rayDirX : %f\n", rayDirX);
		printf("rayDirY : %f\n", rayDirY);
		if (rayDirX == 0)
			rayDirX = INFINITY;
		if (rayDirY == 0)
			rayDirY = INFINITY;
		mapX = (int)vars->player_x;
		mapY = (int)vars->player_y;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		printf("deltaDistX : %f\n", deltaDistX);
		printf("deltaDistY : %f\n", deltaDistY);
		if (rayDirX < 0)
    	{
    		stepX = -1;
			sideDistX = (vars->player_x - mapX) * deltaDistX;
    	}
    	else
    	{
    		stepX = 1;
   			sideDistX = (mapX + 1.0 - vars->player_x) * deltaDistX;
    	}
    	if (rayDirY < 0)
    	{
    		stepY = -1;
    		sideDistY = (vars->player_y - mapY) * deltaDistY;
    	}
    	else
    	{
    		stepY = 1;
    		sideDistY = (mapY + 1.0 - vars->player_y) * deltaDistY;
    	}
		printf("sideDistX : %f\n", sideDistX);
		printf("sideDistY : %f\n", sideDistY);
		printf("posX : %d\n", mapX);
		printf("posY : %d\n", mapY);
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				//printf("char : %c\n", vars->finalmap[mapY][mapX]);
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				//printf("char : %c\n", vars->finalmap[mapY][mapX]);
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			printf("mapX : %d\n", mapX);
			printf("mapY : %d\n", mapY);
			printf("sideDistY : %f\n", sideDistY);
			printf("sideDistX : %f\n", sideDistX);
			printf("array : %c\n", vars->finalmap[mapY][mapX]);
			if (vars->finalmap[mapY][mapX] == '1')
				hit = 1;
			i++;
		}
		while (i < sideDistX * 32)
		{
			mlx_put_pixel(vars->player_img, (vars->player_x * 32) + 16 + (rayDirX * i),
			(vars->player_y * 32) + 16 + (rayDirY * i), 255);
			i++;
		}
		// mlx_image_t *test = mlx_new_image(vars->mlx, 32, 32);
		// ft_memset(test, 255, test->width * test->height * sizeof(int));
		// // mlx_put_pixel(vars->player_img, mapX * 32, mapY * 32, 200);
		// mlx_image_to_window(vars->mlx, test, mapX * 32, mapY * 32);
		// x++;
	}
// }
