#include "../includes/cub3d.h"


int	main(void)
{
	t_vars	vars;

	// CREATE WINDOW
	init_window(&vars);
	// PLAYER ITSELF
	init_player(&vars);
	// VIEW OF PLAYER (NO, EA, SO, WE)
	view_starting_direction(&vars);
	vars.test = NULL;
	mlx_key_hook(vars.mlx, &key_hook, &vars);
	mlx_loop(vars.mlx);
	return (EXIT_SUCCESS);
}