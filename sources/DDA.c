#include <math.h>
#include "../includes/cub3d.h"

#define RGB_BLUE	0xA6C0
#define RGB_WHITE	0xFFFFFFFF
#define RGB_GREEN	0x00996699
#define RGB_YELLOW	0xFFFF007F
#define RGB_PINK	0xFF006699

//calculate ray position and direction
//which box of the map we're in
//length of ray from one x or y-side to next x or y-side
void	starting_values(t_cast *t, t_vars *vars)
{
	t->k = 0;
	t->i = 0;
	t->hit = 0;
	t->side = 0;
	t->lineHeight = 0;
	t->h = vars->m_height;
	t->mapX = (int)vars->player_x;
	t->mapY = (int)vars->player_y;
	t->cameraX = 2 * t->x / t->w - 1;
	t->rayDirX = vars->dir_x + vars->planex * t->cameraX;
	if (!t->rayDirX)
		t->deltaDistX = INFINITY;
	else
		t->deltaDistX = fabs(1 / t->rayDirX);
	t->rayDirY = vars->dir_y + vars->planey * t->cameraX;
	if (!t->rayDirY)
		t->deltaDistY = INFINITY;
	else
		t->deltaDistY = fabs(1 / t->rayDirY);
}

// sideDistance = distance from starting pos
// to the wall hitted on x- or y-side
// deltaDistance = distance from x- or y-line
// to next x- or y line
void	calc_step_and_sidedist(t_cast *t, t_vars *vars)
{
	t->stepX = 1;
	t->stepY = 1;
	if (t->rayDirX < 0)
	{
		t->stepX *= -1;
		t->sideDistX = (vars->player_x - t->mapX) * t->deltaDistX;
	}
	else
		t->sideDistX = (t->mapX + 1 - vars->player_x) * t->deltaDistX;
	if (t->rayDirY < 0)
	{
		t->stepY *= -1;
		t->sideDistY = (vars->player_y - t->mapY) * t->deltaDistY;
	}
	else
		t->sideDistY = (t->mapY + 1 - vars->player_y) * t->deltaDistY;
}

//jump to next map square, either in x-direction, or in y-direction
// until it hits a wall
void	find_hitted_wall(t_cast *t, t_vars *vars)
{
	while (!t->hit)
	{
		if (t->sideDistX < t->sideDistY)
		{
			t->sideDistX += t->deltaDistX;
			t->mapX += t->stepX;
			t->side = Y_SIDE_EA_WE;
			t->side_2 = EA;
			if (t->rayDirX < 0)
				t->side_2 = WE;
		}
		else
		{
			t->sideDistY += t->deltaDistY;
			t->mapY += t->stepY;
			t->side = X_SIDE_NO_S0;
			t->side_2 = SO;
			if (t->rayDirY < 0)
				t->side_2 = NO;
		}
		if (vars->finalmap[(int)t->mapY][(int)t->mapX] == '1')
			t->hit = 1;
	}
}

//calculate lowest and highest pixel to fill in current stripe
// perpendicularWallDistance = ray from cameraplane to wall hit
// to avoid fish-eye effect
// length of rays (drawstart & drawend)
void	calc_perp_wall_drawthings(t_cast *t)
{
	if (t->side == Y_SIDE_EA_WE)
		t->perpWallDist = t->sideDistX - t->deltaDistX;
	if (t->side == X_SIDE_NO_S0)
		t->perpWallDist = t->sideDistY - t->deltaDistY;
	if (t->perpWallDist > 0)
		t->lineHeight = (int)(t->h / t->perpWallDist);
	t->drawStart = (t->h - t->lineHeight) / 2;
	if (t->drawStart < 0)
		t->drawStart = 0;
	t->drawEnd = (t->h + t->lineHeight) / 2;
	if (t->drawEnd >= t->h)
		t->drawEnd = t->h - 1;
}

// for every ray that is shooted
void	dda(void *param)
{
	t_vars	*vars;
	t_cast	t;

	vars = param;
	t.x = 0;
	t.w = vars->m_width;
	while (t.x < t.w)
	{
		starting_values(&t, vars);
		calc_step_and_sidedist(&t, vars);
		find_hitted_wall(&t, vars);
		calc_perp_wall_drawthings(&t);
		draw_everything(&t, vars);
		t.x++;
	}
}
