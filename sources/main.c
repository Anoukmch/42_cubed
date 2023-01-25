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
	}
	else
	{
		printf("Error\nmissing or too much arg\n");
		exit(1);
	}
	// error_exit(NULL, "Error\n./cub3d only takes one arg input\n");
	// CREATE WINDOW
	init_window(&vars);
	// PUT MAP IN WINDOW
	init_map(&vars, map);
	// PLAYER ITSELF
	init_player(&vars);
	// VIEW OF PLAYER (NO, EA, SO, WE)
	view_starting_direction(&vars);
	vars.test = NULL;
	mlx_key_hook(vars.mlx, &key_hook, &vars);
	mlx_loop(vars.mlx);
	return (EXIT_SUCCESS);
}