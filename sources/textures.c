#include "../includes/cub3d.h"

void	init_textures(t_vars *vars)
{
	int	i;

	vars->textures[PLAYER] = mlx_load_png("./sources/pngfiles/player.png");
	vars->textures[SPACES] = mlx_load_png("./sources/pngfiles/spaces.png");
	vars->textures[CORNER_LEFT_UP] = mlx_load_png("./sources/pngfiles/cleftup.png");
	vars->textures[CORNER_LEFT_DOWN] = mlx_load_png("./sources/pngfiles/cleftdown.png");
	vars->textures[CORNER_RIGHT_UP] = mlx_load_png("./sources/pngfiles/crightup.png");
	vars->textures[CORNER_RIGHT_DOWN] = mlx_load_png("./sources/pngfiles/c_r_down.png");
	vars->textures[WALL_LEFT] = mlx_load_png("./sources/pngfiles/wallleft.png");
	vars->textures[WALL_RIGHT] = mlx_load_png("./sources/pngfiles/wallright.png");
	vars->textures[WALL_DOWN] = mlx_load_png("./sources/pngfiles/walldown.png");
	vars->textures[WALL_UP] = mlx_load_png("./sources/pngfiles/wallup.png");
	vars->textures[COLLECTS] = mlx_load_png("./sources/pngfiles/collectible.png");
	vars->textures[EXIT] = mlx_load_png("./sources/pngfiles/exit.png");
	vars->textures[BOX] = mlx_load_png("./sources/pngfiles/box.png");
	i = 0;
	while (i < TEXTURES)
	{
		if (vars->textures[i] == NULL)
			exit(printf("Please check the initialization of your textures!\n"));
		i++;
	}
}