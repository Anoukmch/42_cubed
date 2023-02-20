#include "../includes/cub3d.h"

// PAINTING WALLS IN ONE COLOR
//uint32_t	colors;
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
void	drawing_floor_and_ceiling(t_cast *t, t_vars *vars)
{
	t->k = 0;
	vars = (t_vars *)vars;
	while (t->k < t->h)
	{
		if (t->k <= t->drawStart)
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->ceilingcolor);
		if (t->k >= t->drawEnd)
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->floorcolor);
		t->k++;
	}
}

int	texture_3(mlx_texture_t *tex, t_cast *t, t_vars *vars)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0.0;
	if (t->side == Y_SIDE_EA_WE)
		wall_x = vars->player_y + t->perpWallDist * t->rayDirY;
	else if (t->side == X_SIDE_NO_S0)
		wall_x = vars->player_x + t->perpWallDist * t->rayDirX;
	wall_x -= floor(wall_x);
	tex_x = wall_x * tex->width;
	if ((t->side == Y_SIDE_EA_WE && t->rayDirX > 0)
		|| (t->side == X_SIDE_NO_S0 && t->rayDirY < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	texture_2(t_cast *t, t_vars *vars)
{
	int				y;
	double			step;
	int				line_h;
	int				tex_y;
	double			tex_pos;

	step = 0;
	line_h = (t->drawEnd) - (t->drawStart);
	t->drawStart = fmax(0, (t->h - line_h) / 2);
	step = 1.0 * vars->textures[WE]->height / line_h;
	y = (t->drawStart);
	tex_pos = (t->drawStart - (t->h + line_h) / 2) * step;
	while (y < (t->drawEnd))
	{
		tex_y = (int)tex_pos & (vars->textures[NO]->height - 1);
		tex_pos += step;
		ft_memcpy(&vars->image_3d->pixels[\
			(y * vars->m_width + t->x) * BPP], \
			&vars->textures[t->side_2]->pixels[\
			(tex_y * vars->textures[NO]->height + \
			texture_3(vars->textures[NO], t, vars)) * BPP], BPP);
		y++;
	}
}
