#include <math.h>
#include "../includes/cub3d.h"

#define	RGB_BLUE	0xA6C0
#define RGB_WHITE	0xFFFFFFFF
#define RGB_GREEN	0x00993366
#define RGB_YELLOW	0xFFFF007F
#define RGB_PINK	0xFF006699

#define NO	0
#define EA	1
#define SO	2
#define WE	3
// BLUE: 0xA6C0;
// WHITE: 0xFFFFFFFF;
// GREEN: 0x00993366;
// ORANGE: 0xFF993366;
// YELLOW: 0xFFFF007F;
// PINK: 0xFF006699;

//choose wall color

void	draw_line(void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_put_pixel(win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}



void	dda(t_vars *vars, int color)
{
	int x;
	double w;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int		mapX;
	int		mapY;
	// double time = 0; //time of current frame
  	// double oldTime = 0; //time of previous frame
	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	//what direction to step in x or y-direction (either +1 or -1)
	double stepX;
	double stepY;
	int hit;
	int side;
	int i;

	x = 0;
	w = 1000;
	while (x < w)
	{
		i = 0;
		hit = 0;
		side = 0;
		//calculate ray position and direction
		cameraX = 2 * x / w - 1;
		rayDirX = vars->dir_x + vars->planex * cameraX;
		rayDirY = vars->dir_y + vars->planey * cameraX;
		//which box of the map we're in
		mapX = (int)vars->player_x;
		mapY = (int)vars->player_y;
		//length of ray from one x or y-side to next x or y-side
		if (rayDirX == 0)
			deltaDistX = INFINITY;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = INFINITY;
		else
			deltaDistY = fabs(1 / rayDirY);
		//calculate step and initial sideDist
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
		// perform DDA
		int	is_negative;
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 1; //EA or WE
				is_negative = rayDirX < 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 0; //NO or SO
				is_negative = rayDirY < 0;
			}
			//Check if ray has hit a wall
			if (vars->finalmap[(int)mapY][(int)mapX] > '0')
				hit = 1;
		}
			double perpWallDist;
			int side_2;
			if (side)
			{
				if (is_negative)
					side_2 = NO;
				else
					side_2 = SO;
			}
			else
			{
				if (is_negative)
					side_2 = EA;
				else
					side_2 = WE;
			}
			if (side)
				perpWallDist = sideDistX - deltaDistX;
			else
				perpWallDist = sideDistY - deltaDistY;
			//Calculate height of line to draw on screen
			int lineHeight; // h = the height in pixels of the screen
			double	h;
			h = vars->m_height * 32;
			lineHeight = 0;
			if (perpWallDist > 0)
				lineHeight = (int)(h / perpWallDist);
			printf("h: %f\n", h);
			printf("Lineheight: %d\n", lineHeight);
			//calculate lowest and highest pixel to fill in current stripe
			int drawStart;
			drawStart = (h -lineHeight) / 2;
			if (drawStart < 0)
				drawStart = 0;
			printf("drawSTART: %d\n", drawStart);
			int drawEnd;
			drawEnd = (h + lineHeight) / 2;
			printf("drawEnd: %d\n", drawEnd);
			if (drawEnd >= h)
				drawEnd = h - 1;
			
			// PRINTING
			//give x and y sides different brightness
			int	k;

			k = 0;
			while (k < h)
			{
				uint32_t colors;
				if (k <= drawStart)
				{
					colors = RGB_PINK;
      				if (side == 1) {colors = colors / 2;}
					mlx_put_pixel(vars->player_img, x, k, RGB_PINK);
				}
				if (k >= drawEnd)
				{
					colors = RGB_GREEN;
      				if (side == 1) {colors = colors / 2;}
					mlx_put_pixel(vars->player_img, x, k, RGB_GREEN);
				}
				k++;
			}
			color = 0;
		x++;
	}
}

			// switch(vars->finalmap[(int)mapY][(int)mapX])
			// {
			// 	case 1:  color = RGB_PINK;  break; //red
			// 	case 2:  color = RGB_GREEN;  break; //green
			// 	// case 3:  color = RGB_BLUE;   break; //blue
			// 	// case 4:  color = RGB_WHITE;  break; //white
			// 	default: color = RGB_YELLOW; break; //yellow
    		// }