#include <math.h>
#include "../includes/cub3d.h"

void	dda(t_vars *vars)
{
	int x;
	double w;
	double posX;
	double posY;
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

	x = 0;
	w = 1000000;
	posX = 22;
	posY = 12;
	while (x < w)
	{
		hit = 0;
		side = 0;
		cameraX = 2 * x / w - 1;
		rayDirX = vars->dir_x + vars->planex * cameraX;
		rayDirY = vars->dir_y + vars->planey * cameraX;
		get_view(vars, 255, rayDirX, rayDirY);
		if (rayDirX == 0)
			rayDirX = INFINITY;
		if (rayDirY == 0)
			rayDirY = INFINITY;
		mapX = (int)vars->player_x;
		mapY = (int)vars->player_y;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		if (rayDirX < 0)
    	{
    		stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
    	}
    	else
    	{
    		stepX = 1;
   			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    	}
    	if (rayDirY < 0)
    	{
    		stepY = -1;
    		sideDistY = (posY - mapY) * deltaDistY;
    	}
    	else
    	{
    		stepY = 1;
    		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    	}
		// while (hit == 0)
		// {
		// 	if (sideDistX < sideDistY)
		// 	{
		// 		sideDistX += deltaDistX;
		// 		mapX += stepX;
		// 		side = 0;
		// 	}
		// 	else
		// 	{
		// 		sideDistY += deltaDistY;
		// 		mapY += stepY;
		// 		side = 1;
		// 	}
		// 	if (vars->finalmap[mapX][mapY] > 0)
		// 		hit = 1;
		// }
		x++;
	}
}
