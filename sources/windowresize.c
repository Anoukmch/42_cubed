#include "../includes/cub3d.h"

void	windowresize(int32_t width, int32_t height, void *param)
{
	t_vars	*vars;

	vars = param;
	vars->m_height = height;
	vars->m_width = width;
	mlx_resize_image(vars->image_3d, vars->m_width, vars->m_height);
}
