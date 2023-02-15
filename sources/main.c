#include "../includes/cub3d.h"

void	init(t_vars *vars, t_map *map)
{
	init_window(vars, map);
	init_textures(vars, map);
	init_player_and_views(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	*map;
	char	*line;

	map = NULL;
	if (argc == 2)
	{
		if (check_extension(argv[1]) == 0)
			error_exit("Error\nWrong input file extension\n");
		initialize(argv[1], &map);
		line = texture_and_colors_pars(map);
		get_finalmap(map, line);
		vars.finalmap = map->cmap;
		vars.linesofmap = map->maplines;
	}
	else
		error_exit("Error\nmissing or too much arg\n");
	transform_colors(&vars, map);
	init(&vars, map);
	mlx_resize_hook(vars.mlx, &windowresize, &vars);
	mlx_loop_hook(vars.mlx, &dda, &vars);
	mlx_key_hook(vars.mlx, &key_hook, &vars);
	mlx_loop(vars.mlx);
	free_text(&vars);
	return (EXIT_SUCCESS);
}

// error_exit(NULL, "Error\n./cub3d only takes one arg input\n");
