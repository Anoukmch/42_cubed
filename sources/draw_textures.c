#include "../includes/cub3d.h"

int	texture_x_value(mlx_texture_t *tex, t_cast *t, t_vars *vars)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0;
	if (t->side == Y_SIDE_EA_WE)
		wall_x = vars->player_y + t->perpWallDist * t->rayDirY;
	if (t->side == X_SIDE_NO_S0)
		wall_x = vars->player_x + t->perpWallDist * t->rayDirX;
	wall_x -= (int)wall_x;
	tex_x = wall_x * tex->width;
	if ((t->side == Y_SIDE_EA_WE && t->rayDirX > 0)
		|| (t->side == X_SIDE_NO_S0 && t->rayDirY < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_everything(t_cast *t, t_vars *vars)
{
	double			tex_pos;
	double			step;
	int				tex_y;

	t->drawStart = fmax(0, (t->h - (t->drawEnd - t->drawStart)) / 2);
	step = 1.0 * vars->textures[NO]->height / (t->drawEnd - t->drawStart);
	tex_pos = (t->drawStart - (t->h + (t->drawEnd - t->drawStart)) / 2) * step;
	while (t->k < t->h)
	{
		if (t->k <= t->drawStart)
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->ceilingcolor);
		else if (t->k >= t->drawEnd)
			mlx_put_pixel(vars->image_3d, t->x, t->k, vars->floorcolor);
		if (t->k < t->drawEnd && t->k >= t->drawStart)
		{
			tex_y = (int)tex_pos & (vars->textures[NO]->height - 1);
			tex_pos += step;
			ft_memcpy(&vars->image_3d->pixels[(t->k * vars->m_width + t->x) \
				* BPP], &vars->textures[t->side_2]->pixels[\
				(tex_y * vars->textures[NO]->height + \
				texture_x_value(vars->textures[NO], t, vars)) * BPP], BPP);
		}
		t->k++;
	}
}
