#include "../includes/cub3d.h"

void door(mlx_key_data_t keydata, void *param)
{
	t_vars *vars;

	vars = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		open_door(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map;

	if (argc != 2 && check_extension(argv[1]))
	{
		ft_putstr_fd("Error\ncheck arg input\n", 2);
		return (0);
	}
	init_map(argv[1], &map);
	get_map(&map);
	vars.finalmap = map.cmap;
	vars.linesofmap = map.maplines + 1;
	transform_colors(&vars, &map);
	init_vars(&vars, &map);
	init_minimap(&vars);
	mlx_resize_hook(vars.mlx, &windowresize, &vars);
	mlx_loop_hook(vars.mlx, &dda, &vars);
	mlx_key_hook(vars.mlx, &door, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_text_img(&vars);
	free_struct(&map);
	return (EXIT_SUCCESS);
}
