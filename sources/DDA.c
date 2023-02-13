#include <math.h>
#include "../includes/cub3d.h"

#define RGB_BLUE	0xA6C0
#define RGB_WHITE	0xFFFFFFFF
#define RGB_GREEN	0x00996699
#define RGB_YELLOW	0xFFFF007F
#define RGB_PINK	0xFF006699

#define texWidth 32
#define texHeight 32
// BLUE: 0xA6C0;
// WHITE: 0xFFFFFFFF;
// GREEN: 0x00993366;
// ORANGE: 0xFF993366;
// YELLOW: 0xFFFF007F;
// PINK: 0xFF006699;

//calculate ray position and direction
//which box of the map we're in
//length of ray from one x or y-side to next x or y-side
void	starting_values(t_cast *t, t_vars *vars)
{
	t->i = 0;
	t->hit = 0;
	t->side = 0;
	t->cameraX = 2 * t->x / t->w - 1;
	t->rayDirX = vars->dir_x + vars->planex * t->cameraX;
	t->rayDirY = vars->dir_y + vars->planey * t->cameraX;
	t->mapX = (int)vars->player_x;
	t->mapY = (int)vars->player_y;
	if (t->rayDirX == 0)
		t->deltaDistX = INFINITY;
	else
		t->deltaDistX = fabs(1 / t->rayDirX);
	if (t->rayDirY == 0)
		t->deltaDistY = INFINITY;
	else
		t->deltaDistY = fabs(1 / t->rayDirY);
}

//calculate step and initial sideDist
void	calc_step_and_sidedist(t_cast *t, t_vars *vars)
{
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

// perform DDA
//jump to next map square, either in x-direction, or in y-direction
// t->side = 1--> EA or WE
// t->side = 0--> NO or SO
//Check if ray has hit a wall
void	find_hitted_wall(t_cast *t, t_vars *vars)
{
	while (t->hit == 0)
	{
		if (t->sideDistX < t->sideDistY)
		{
			t->sideDistX += t->deltaDistX;
			t->mapX += t->stepX;
			t->side = 1;
			t->is_negative = t->rayDirX < 0;
		}
		else
		{
			t->sideDistY += t->deltaDistY;
			t->mapY += t->stepY;
			t->side = 0;
			t->is_negative = t->rayDirY < 0;
		}
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

int	texture_3(mlx_texture_t *tex, t_cast *t, t_vars *vars)
{
	double wallX;

	if (t->side == 0)
		wallX = vars->player_y + t->perpWallDist * t->rayDirY;
	else
		wallX = vars->player_x + t->perpWallDist * t->rayDirX;
	wallX -= (int)wallX;
	int texX = (int)(wallX * (double)tex->width);
	if(t->side == 0 && t->rayDirX > 0)
		texX = tex->width - texX - 1;
	if(t->side == 1 && t->rayDirY < 0)
		texX = tex->width - texX - 1;
	return (texX);
}

void	texture_2(t_cast *t, t_vars *vars)
{
	mlx_texture_t *tex;
	int y;
	double step;
	int line_h;

	step = 0;
	tex = vars->textures[WALL_DOWN];
	line_h = t->drawEnd - t->drawStart;
	t->drawStart = (t->h - line_h) / 2;
	double texPos = (t->drawStart - (t->h + line_h) / 2) * step;
	step = 1.0 * tex->height / line_h;
	y = (t->drawStart * 32);
	while (y < (t->drawEnd * 32))
	{
		int texY = (int)texPos & (tex->height - 1);
		texPos += step;
		// ft_memset(&vars->image_3d->pixels[((y * vars->m_width + t->x) * 32)],
		// tex->pixels[(texY * texHeight + texture_3(t, vars)) * 32], 32 * 32);
		ft_memcpy(&vars->image_3d->pixels[((y * vars->m_width + t->x))],
		&tex->pixels[texY * tex->height + texture_3(tex, t, vars)], 1);
		y++;
	}
}

// void	printing_textures(t_cast *t, t_vars *vars)
// {
	//texturing calculations
	//int texNum = vars->finalmap[t->mapY][t->mapX] - 1;
	// double wallX;
	// if (t->side == 0)
	// 	wallX = vars->player_y + t->perpWallDist * t->rayDirY;
	// else
	// 	wallX = vars->player_x + t->perpWallDist * t->rayDirX;
	// wallX -= (int)wallX;
	//x coordinate on the texture
	// int texX = (int)(wallX * (double)texWidth);
	// if(t->side == 0 && t->rayDirX > 0)
	// 	texX = texWidth - texX - 1;
	// if(t->side == 1 && t->rayDirY < 0)
	// 	texX = texWidth - texX - 1;
	//double step = 1.0 * texHeight / t->lineHeight;
	//double texPos = (t->drawStart - t->h / 2 + t->lineHeight / 2) * step;
	// while (y < t->drawEnd)
	// {
	// 	int texY = (int)texPos & (texHeight - 1);
	// 	texPos += step;
	// 	ft_memcpy(&vars->image_3d->pixels[((y * vars->m_width + t->x) * 4)],
	// 	&tex->pixels[(texY * texHeight + texX) * 4], 4);
	// 	y++;
	// }
// }

//Calculate height of line to draw on screen
//calculate lowest and highest pixel to fill in current stripe
void	calc_perp_wall_drawthings(t_cast *t, t_vars *vars)
{
	if (t->side)
		t->perpWallDist = t->sideDistX - t->deltaDistX;
	else
		t->perpWallDist = t->sideDistY - t->deltaDistY;
	t->h = vars->m_height * 32;
	t->lineHeight = 0;
	if (t->perpWallDist > 0)
		t->lineHeight = (int)(t->h / t->perpWallDist);
	t->drawStart = (t->h - t->lineHeight) / 2;
	if (t->drawStart < 0)
		t->drawStart = 0;
	t->drawEnd = (t->h + t->lineHeight) / 2;
	if (t->drawEnd >= t->h)
		t->drawEnd = t->h - 1;
}

void	printing_walls(t_cast *t, t_vars *vars)
{
	//uint32_t	colors;

	t->k = 0;
	while (t->k < t->h)
	{
		if (t->k <= t->drawStart)
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->ceilingcolor);
		if (t->k >= t->drawEnd)
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->floorcolor);
		// if (t->drawStart + t->k < t->drawEnd)
		// {
		// 	colors = RGB_GREEN;
		// 	if (t->side == 1)
		// 		mlx_put_pixel(vars->image_3d,
		// 			t->x, t->drawStart + t->k, colors / 2);
		// 	else
		// 		mlx_put_pixel(vars->image_3d,
		// 			t->x, t->drawStart + t->k, colors);
		// }
		t->k++;
	}
}

void	dda(void *param)
{
	t_vars	*vars;
	t_cast	t;

	vars = param;
	t.x = 0;
	t.w = vars->m_width * 32;
	while (t.x < t.w)
	{
		starting_values(&t, vars);
		calc_step_and_sidedist(&t, vars);
		find_hitted_wall(&t, vars);
		find_side_of_hitted_wall(&t);
		calc_perp_wall_drawthings(&t, vars);
		texture_2(&t, vars);
		printing_walls(&t, vars);
		t.x++;
	}
}

void	dda_overwriting(t_vars *vars)
{
	t_cast	t;

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
		while (t.k < t.h)
		{
			mlx_put_pixel(vars->image_3d, t.x, t.k, 0);
			t.k++;
		}
	t.x++;
	}
}
