#include "../includes/cub3d.h"

void	draw_floor_and_ceiling(t_cast *t, t_vars *vars)
{
	t->iter = 0;
	while (t->iter < vars->m_height)
	{
		if (t->iter <= t->draw_start)
			mlx_put_pixel(vars->image_3d, t->x, t->iter, vars->ceilingcolor);
		else if (t->iter > t->draw_end)
			mlx_put_pixel(vars->image_3d, t->x, t->iter, vars->floorcolor);
		t->iter++;
	}
}

// wall_x = exact pos where ray hits wall
// tex_x = pos in texture to take pixel from
int	texture_x_value(mlx_texture_t *tex, t_cast *t, t_vars *vars)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0;
	if (t->is_ea_we == Y_SIDE_EA_WE)
		wall_x = vars->player_y + t->perp_wall_dist * t->raydir_y;
	if (t->is_ea_we == X_SIDE_NO_S0)
		wall_x = vars->player_x + t->perp_wall_dist * t->raydir_x;
	wall_x -= (int)wall_x;
	tex_x = wall_x * tex->width;
	if (t->which_card_pt == NO || t->which_card_pt == WE)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

int	pick_txt(t_cast *t)
{
	if (t->hit == 1)
		return (t->which_card_pt);
	else if (t->door == 1)
		return (DOOR);
	return (0);
}

void	draw_walls(t_cast *t, t_vars *vars)
{
	double			tex_pos;
	double			step;
	int				tex_y;
	int				tex_x;
	int				lineh;

	lineh = t->draw_end - t->draw_start;
	step = 1.0 * 32 / lineh;
	t->draw_start = fmax(0, (vars->m_height - (lineh)) / 2);
	tex_pos = (t->draw_start - (vars->m_height + (lineh)) / 2) * step;
	tex_x = texture_x_value(vars->textures[t->which_card_pt], t, vars);
	while (t->draw_start <= t->draw_end)
	{
		tex_y = fmax(0, (int)tex_pos + (32 - 1));
		tex_pos += step;
		ft_memcpy(&vars->image_3d->pixels[(t->draw_start * \
		(int)vars->m_width + t->x) * BPP], &vars->textures[\
		pick_txt(t)]->pixels[(tex_y * 32 + tex_x) * BPP], BPP);
		t->draw_start++;
	}
}
