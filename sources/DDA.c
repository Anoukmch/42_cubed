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
	t->iter = 0;
	t->hit = 0;
	t->door = 0;
	t->is_ea_we = 0;
	t->wall_line = 0;
	t->map_x = (int)vars->player_x;
	t->map_y = (int)vars->player_y;
	t->camera_x = 2 * t->x / vars->m_width - 1;
	t->raydir_x = vars->dir_x + vars->plane_x * t->camera_x;
	if (!t->raydir_x)
		t->deltadist_x = INFINITY;
	else
		t->deltadist_x = fabs(1 / t->raydir_x);
	t->raydir_y = vars->dir_y + vars->plane_y * t->camera_x;
	if (!t->raydir_y)
		t->deltadist_y = INFINITY;
	else
		t->deltadist_y = fabs(1 / t->raydir_y);
}

// sideDistance = distance from starting pos
// to the wall hitted on x- or y-side
// deltaDistance = distance from x- or y-line
// to next x- or y line
void	calc_step_and_sidedist(t_cast *t, t_vars *vars)
{
	t->step_x = 1;
	t->step_y = 1;
	if (t->raydir_x < 0)
	{
		t->step_x *= -1;
		t->sidedist_x = (vars->player_x - t->map_x) * t->deltadist_x;
	}
	else
		t->sidedist_x = (t->map_x + 1 - vars->player_x) * t->deltadist_x;
	if (t->raydir_y < 0)
	{
		t->step_y *= -1;
		t->sidedist_y = (vars->player_y - t->map_y) * t->deltadist_y;
	}
	else
		t->sidedist_y = (t->map_y + 1 - vars->player_y) * t->deltadist_y;
}

//jump to next map square, either in x-direction, or in y-direction
// until it hits a wall
void	find_hitted_wall(t_cast *t, t_vars *vars)
{
	while (!t->hit && !t->door)
	{
		if (t->sidedist_x < t->sidedist_y)
		{
			t->sidedist_x += t->deltadist_x;
			t->map_x += t->step_x;
			t->is_ea_we = Y_SIDE_EA_WE;
			t->which_card_pt = EA;
			if (t->raydir_x < 0)
				t->which_card_pt = WE;
		}
		else
		{
			t->sidedist_y += t->deltadist_y;
			t->map_y += t->step_y;
			t->is_ea_we = X_SIDE_NO_S0;
			t->which_card_pt = SO;
			if (t->raydir_y < 0)
				t->which_card_pt = NO;
		}
		if (vars->finalmap[(int)t->map_y][(int)t->map_x] == '1')
			t->hit = 1;
		else if (vars->finalmap[(int)t->map_y][(int)t->map_x] == '2')
		{
			t->door = 1;
			vars->door_x = (int)t->map_x;
			vars->door_y = (int)t->map_y;
		}
	}
}

//calculate lowest and highest pixel to fill in current stripe
// perpendicularWallDistance = ray from cameraplane to wall hit
// to avoid fish-eye effect
// length of rays (draw_start & draw_end)
void	calc_perp_wall_drawthings(t_cast *t, t_vars	*vars)
{
	if (t->is_ea_we == Y_SIDE_EA_WE)
		t->perp_wall_dist = t->sidedist_x - t->deltadist_x;
	if (t->is_ea_we == X_SIDE_NO_S0)
		t->perp_wall_dist = t->sidedist_y - t->deltadist_y;
	if (t->perp_wall_dist > 0)
		t->wall_line = (int)(vars->m_height / t->perp_wall_dist);
	vars->perp_wall_dist_2 = t->perp_wall_dist;
	t->draw_start = (vars->m_height - t->wall_line) / 2;
	if (t->draw_start < 0)
		t->draw_start = 0;
	t->draw_end = (vars->m_height + t->wall_line) / 2;
	if (t->draw_end >= vars->m_height)
		t->draw_end = vars->m_height - 1;
}

// for every ray that is shooted
void	dda(void *param)
{
	t_vars	*vars;
	t_cast	t;

	vars = param;
	t.x = 0;
	key_hook(vars);
	while (t.x < vars->m_width)
	{
		starting_values(&t, vars);
		calc_step_and_sidedist(&t, vars);
		find_hitted_wall(&t, vars);
		calc_perp_wall_drawthings(&t, vars);
		draw_everything(&t, vars);
		t.x++;
	}
}
