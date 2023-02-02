#include "../includes/cub3d.h"

void	windowresize(int32_t height, int32_t width, void *param)
{
	t_vars	*vars;

	vars = param;
	vars->m_height = height;
	vars->m_width = width;
}
