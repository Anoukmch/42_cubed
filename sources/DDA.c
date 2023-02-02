#include <math.h>
#include "../includes/cub3d.h"

#define RGB_BLUE	0xA6C0
#define RGB_WHITE	0xFFFFFFFF
#define RGB_GREEN	0x00996699
#define RGB_YELLOW	0xFFFF007F
#define RGB_PINK	0xFF006699

// BLUE: 0xA6C0;
// WHITE: 0xFFFFFFFF;
// GREEN: 0x00993366;
// ORANGE: 0xFF993366;
// YELLOW: 0xFFFF007F;
// PINK: 0xFF006699;

void	starting_values(t_cast *t, t_vars *vars)
{
	t->i = 0;
	t->hit = 0;
	t->side = 0;
	//calculate ray position and direction
	t->cameraX = 2 * t->x / t->w - 1;
	t->rayDirX = vars->dir_x + vars->planex * t->cameraX;
	t->rayDirY = vars->dir_y + vars->planey * t->cameraX;
	//which box of the map we're in
	t->mapX = (int)vars->player_x;
	t->mapY = (int)vars->player_y;
	//length of ray from one x or y-side to next x or y-side
	if (t->rayDirX == 0)
		t->deltaDistX = INFINITY;
	else
		t->deltaDistX = fabs(1 / t->rayDirX);
	if (t->rayDirY == 0)
		t->deltaDistY = INFINITY;
	else
		t->deltaDistY = fabs(1 / t->rayDirY);
}

void	calc_step_and_sidedist(t_cast *t, t_vars *vars)
{
	//calculate step and initial sideDist
	if (t->rayDirX < 0)
	{
		t->stepX = -1;
		t->sideDistX = (vars->player_x - t->mapX) * t->deltaDistX;
	}
	else
	{
		t->stepX = 1;
		t->sideDistX = (t->mapX + 1.0 - vars->player_x) * t->deltaDistX;
	}
	if (t->rayDirY < 0)
	{
		t->stepY = -1;
		t->sideDistY = (vars->player_y - t->mapY) * t->deltaDistY;
	}
	else
	{
		t->stepY = 1;
		t->sideDistY = (t->mapY + 1.0 - vars->player_y) * t->deltaDistY;
	}
}

void	find_hitted_wall(t_cast *t, t_vars *vars)
{
	// perform DDA
	while (t->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (t->sideDistX < t->sideDistY)
		{
			t->sideDistX += t->deltaDistX;
			t->mapX += t->stepX;
			t->side = 1; //EA or WE
			t->is_negative = t->rayDirX < 0;
		}
		else
		{
			t->sideDistY += t->deltaDistY;
			t->mapY += t->stepY;
			t->side = 0; //NO or SO
			t->is_negative = t->rayDirY < 0;
		}
		//Check if ray has hit a wall
		if (vars->finalmap[(int)t->mapY][(int)t->mapX] > '0')
			t->hit = 1;
	}
}

void	find_side_of_hitted_wall(t_cast *t)
{
	if (t->side)
	{
		if (t->is_negative)
			t->side_2 = NO;
		else
			t->side_2 = SO;
	}
	else
	{
		if (t->is_negative)
			t->side_2 = EA;
		else
			t->side_2 = WE;
	}
}

void	calc_perp_wall_drawthings(t_cast *t, t_vars *vars)
{
	if (t->side)
		t->perpWallDist = t->sideDistX - t->deltaDistX;
	else
		t->perpWallDist = t->sideDistY - t->deltaDistY;
	//Calculate height of line to draw on screen
	t->h = vars->m_height * 32;
	t->lineHeight = 0;
	if (t->perpWallDist > 0)
		t->lineHeight = (int)(t->h / t->perpWallDist);
	//calculate lowest and highest pixel to fill in current stripe
	t->drawStart = (t->h - t->lineHeight) / 2;
	if (t->drawStart < 0)
		t->drawStart = 0;
	t->drawEnd = (t->h + t->lineHeight) / 2;
	if (t->drawEnd >= t->h)
		t->drawEnd = t->h - 1;
}

void	printing_walls(t_cast *t, t_vars *vars)
{
	// PRINTING
	//give x and y sides different brightness
	vars = (t_vars *)vars;	
	uint32_t	colors;

	t->k = 0;
	while (t->drawStart + t->k < t->drawEnd)
	{
		colors = RGB_GREEN;
		if (t->side == 1)
			mlx_put_pixel(vars->image_3d, t->x, t->drawStart + t->k, colors / 2);
		else
			mlx_put_pixel(vars->image_3d, t->x, t->drawStart + t->k, colors);
		t->k++;
	}
	t->k = 0;
	while (t->k < t->h)
	{
		if (t->k <= t->drawStart) //CEILING COLOR
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->ceilingcolor);
		if (t->k >= t->drawEnd) //FLOOR COLOR
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->floorcolor);
		t->k++;
	}
}

void	dda(void *param)
{
	t_vars	*vars;

	vars = param;
	t_cast t;

	t.x = 0;
	t.w = vars->m_width * 32;
	while (t.x < t.w)
	{
		starting_values(&t, vars);
		calc_step_and_sidedist(&t, vars);
		find_hitted_wall(&t, vars);
		find_side_of_hitted_wall(&t);
		calc_perp_wall_drawthings(&t, vars);
		printing_walls(&t, vars);
		t.x++;
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

void	dda_overwriting(t_vars *vars)
{
	t_cast t;

	t.x = 0;
	t.w = vars->m_width * 32;
	while (t.x < t.w)
	{
		starting_values(&t, vars);
		calc_step_and_sidedist(&t, vars);
		find_hitted_wall(&t, vars);
		find_side_of_hitted_wall(&t);
		calc_perp_wall_drawthings(&t, vars);
	t.k = 0;
	while (t.drawStart + t.k < t.drawEnd)
	{
		mlx_put_pixel(vars->image_3d, t.x, t.drawStart + t.k, 0);
		t.k++;
	}
	t.x++;
	}
	t.k = 0;
	while (t.k < t.h)
	{
		if (t.k <= t.drawStart)
			mlx_put_pixel(vars->image_3d, t.x, t.k, 0);
		if (t.k >= t.drawEnd)
			mlx_put_pixel(vars->image_3d, t.x, t.k, 0);
		t.k++;
	}
}
