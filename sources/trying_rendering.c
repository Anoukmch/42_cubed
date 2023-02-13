#include "../includes/cub3d.h"

// void	set_image_pixel(t_vars *vars, int x, int y, int color)
// {
// 	int	pixel;

// 	pixel = y * (vars->walls->width / 4) + x;
// 	mlx_
// 	vars->walls->pixels = color;
// }

// void print_textures(t_cast *t, t_vars *vars, int color)
// {
// 	int	y;

// 	vars->walls = mlx_new_image(vars->mlx, vars->m_width, vars->m_height);
// 	if (!vars->walls)
// 		exit(printf("image mistake walls\n"));
// 	y = t->drawStart * 32;
// 	while (y < (t->drawEnd * 32))
// 	{
// 		mlx_put_pixel(vars->walls, t->x, y, color);
// 		// set_image_pixel(vars, t->x, y, color);
// 		y++;
// 	}
// }