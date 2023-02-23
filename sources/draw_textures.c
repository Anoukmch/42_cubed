#include "../includes/cub3d.h"

// wall_x = exact pos where ray hits wall
// tex_x = 
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

// draw floor & ceiling
// (from 0 to draw start, from draw end to window end)
// inbetween = walls

void	draw_everything(t_cast *t, t_vars *vars)
{
	double			tex_pos;
	double			step;
	int				tex_y;
	int				tex_x;

	t->draw_start = fmax(0, (vars->m_height - (t->draw_end - t->draw_start)) / 2);
	step = 1.0 * 32 / (t->draw_end - t->draw_start);
	tex_pos = (t->draw_start - (vars->m_height \
			+ (t->draw_end - t->draw_start)) / 2) * step;
	tex_x = texture_x_value(vars->textures[t->which_card_pt], t, vars);
	while (t->iter < vars->m_height)
	{
		if (t->iter < t->draw_start)
			mlx_put_pixel(vars->image_3d, t->x, t->iter, vars->ceilingcolor);
		else if (t->iter > t->draw_end)
			mlx_put_pixel(vars->image_3d, t->x, t->iter, vars->floorcolor);
		if (t->iter <= t->draw_end && t->iter >= t->draw_start)
		{
			tex_y = (int)tex_pos & (32 - 1);
			tex_pos += step;
			ft_memcpy(&vars->image_3d->pixels[(t->iter * \
			(int)vars->m_width + t->x) * BPP], &vars->textures[\
			pick_txt(t)]->pixels[(tex_y * 32 + tex_x) * BPP], BPP);
		}
		t->iter++;
	}
}
