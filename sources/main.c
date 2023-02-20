#include "../includes/cub3d.h"

void	initialize(char *mapfile, t_map *map)
{
	map->maplines = 0;
	map->line = NULL;
	map->rgb_f = NULL;
	map->rgb_c = NULL; // test, try to remove that to see error msg
	map->cmap = NULL;
	map->text_path = NULL;
	map->fd = open(mapfile, O_RDONLY);
	if (map->fd < 0)
		error_exit("Error\nOpen fail");
	map->text_path = ft_calloc(5, sizeof(char*));;
	if (!map->text_path)
		error_exit("Error\nAllocation fail");
	map->m_argv = mapfile;
	map->player = 0;
	map->maplines = 0;
	map->mapstart = 0;
}

void	init(t_vars *vars, t_map *map)
{
	init_window(vars, map);
	init_textures(vars, map);
	init_player_and_views(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map;

	if (argc == 2)
	{
		if (check_extension(argv[1]) == 0)
		{
			ft_putstr_fd("Error\nWrong input file\n", 2);
			return (1);
		}
		initialize(argv[1], &map);
		texture_and_colors_pars(&map);
		get_finalmap(&map);
		vars.finalmap = map.cmap;
		vars.linesofmap = map.maplines;
	}
	else
		error_exit("Error\nmissing or too much arg\n");
	transform_colors(&vars, &map);
	init(&vars, &map);
	mlx_resize_hook(vars.mlx, &windowresize, &vars);
	mlx_loop_hook(vars.mlx, &dda, &vars);
	mlx_key_hook(vars.mlx, &key_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_text_img(&vars);
	free_struct(&map);
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}

// error_exit(NULL, "Error\n./cub3d only takes one arg input\n");
