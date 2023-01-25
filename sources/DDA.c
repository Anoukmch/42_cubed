#include <math.h>
#include "../includes/cub3d.h"

void	dda(t_vars vars)
{
	int x;
	double w;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;

	x = 0;
	w = 32;
	posX = 22;
	posY = 12;
	dirX = -1;
	dirY = 0;
	planeX = 0;
	planeY = 0.66;
	mapX = (int)posX;
	mapY = (int)posY;
	while (x < w)
	{
		cameraX = 2 * x / w - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		x++;
	}
	if (rayDirX == 0)
		rayDirX = INFINITY;
	if (rayDirY == 0)
		rayDirY = INFINITY;
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
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (vars->finalmap[mapX][mapY] > 0)
			hit = 1;
	}
}
