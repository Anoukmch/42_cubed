#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	*map;

	if (argc == 2)
	{
		if (check_extension(argv[1]) == 0)
		{
			printf("Error\nWrong input file extension\n");
			exit(1);
		}
		//error_exit(NULL, "Error\nWrong input file extension\n");
		initialize(argv[1], &map);
		parsing(map);
		vars.finalmap = map->cmap;
		vars.linesofmap = map->maplines;
	}
	else
	{
		printf("Error\nmissing or too much arg\n");
		exit(1);
	}
	// GET TRANSFORMED COLORS FOR FLOOR AND CEILING
	transform_colors(&vars, map);
	// error_exit(NULL, "Error\n./cub3d only takes one arg input\n");
	// CREATE WINDOW
	init_window(&vars, map);
	init_textures(&vars);
	init_player_and_views(&vars);
	// WINDOW RESIZING
	mlx_resize_hook(vars.mlx, &windowresize, &vars);
	mlx_loop_hook(vars.mlx, &dda, &vars);
	mlx_key_hook(vars.mlx, &key_hook, &vars);
	mlx_loop(vars.mlx);
	return (EXIT_SUCCESS);
}
