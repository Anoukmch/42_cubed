#include "../includes/cub3d.h"

// Check the path format : it can be anything
int	check_texture_path(char *line, int indic)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == '\t' || line[i] == ' ')
			i++;
		else if (line[i] == '.' && line[i + 1] == '/' && line[i + 2]
			&& line[i + 2] >= 33 && line[i + 2] <= 126
			&& line[i + 2] != '.' && line[i + 2] != '/' && line[i + 2] != '\\')
			return (indic);
		else
			error_exit("Error\nWrong file path : check input file");
	}
	return (error_exit("Error\nNo file path : check input file"));
}

void	init_textures(t_vars *vars)
{
	int	i;

	vars->textures[PLAYER] = mlx_load_png("./pngfiles/player.png");
	vars->textures[SPACES] = mlx_load_png("./pngfiles/spaces.png");
	vars->textures[CORNER_LEFT_UP] = mlx_load_png("./pngfiles/cleftup.png");
	vars->textures[CORNER_LEFT_DOWN] = mlx_load_png("./pngfiles/cleftdown.png");
	vars->textures[CORNER_RIGHT_UP] = mlx_load_png("./pngfiles/crightup.png");
	vars->textures[CORNER_RIGHT_DOWN] = mlx_load_png("./pngfiles/c_r_down.png");
	vars->textures[WALL_LEFT] = mlx_load_png("./pngfiles/wallleft.png");
	vars->textures[WALL_RIGHT] = mlx_load_png("./pngfiles/wallright.png");
	vars->textures[WALL_DOWN] = mlx_load_png("./pngfiles/color.png");
	vars->textures[WALL_UP] = mlx_load_png("./pngfiles/cat.png");
	vars->textures[COLLECTS] = mlx_load_png("./pngfiles/collectible.png");
	vars->textures[EXIT] = mlx_load_png("./pngfiles/exit.png");
	vars->textures[BOX] = mlx_load_png("./pngfiles/box.png");
	i = 0;
	while (i < TEXTURES)
	{
		if (vars->textures[i] == NULL)
			exit(printf("Please check the initialization of your textures!\n"));
		i++;
	}
}
