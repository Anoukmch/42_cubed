#include "../includes/cub3d.h"

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		playerup(vars);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		playerdown(vars);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		playerleft(vars);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		playerright(vars);
}

static void	mapsettings(t_vars *vars, char **argv)
{
	readingmap(argv, vars);
	if (vars->m_width > 60 || vars->m_height > 35)
	{
		ft_printf("Map error: Your map is too big!\n");
		exit_and_free(vars, 1);
	}
	rectangle_check(vars);
	vars->mlx = mlx_init(vars->m_width * 32,
			vars->m_height * 32, "solong", false);
	if (vars->mlx == NULL)
		exit_and_free(vars, 1);
	ft_init_textures(vars);
	check_texturesize(vars);
}

static void	argvcheck(int argc, char **argv)
{
	char	*file;
	char	*ending;

	if (argc < 2)
		exit (ft_printf("Error: Too few arguments!\n"));
	if (argc > 2)
		exit (ft_printf("Error: Too many arguments!\n"));
	file = ".ber";
	ending = ft_strrchr(argv[1], '.');
	if (ending == 0 || ft_strlen(ending) != 4)
		exit (ft_printf("Error: Check the name of your map file!\n"));
	if (ft_memcmp(ending, file, 4) != 0)
		exit (ft_printf("Error: Check the name of your map file!\n"));
}
int main(int argc, char **argv)
{
	t_vars	vars;

	argvcheck(argc, argv);
	ft_memset(&vars, 0, sizeof(t_vars));
	mapsettings(&vars, argv);
	vars.bg_img = mlx_new_image(vars.mlx,
			vars.m_width * 32, vars.m_height * 32);
	vars.map_img = mlx_new_image(vars.mlx,
			vars.m_width * 32, vars.m_height * 32);
	vars.player_img = mlx_texture_to_image(vars.mlx, vars.textures[PLAYER]);
	if (vars.bg_img == NULL || vars.map_img == NULL
		|| vars.player_img == NULL)
		exit_and_free(&vars, 1);
	paintingmap(&vars);
	mlx_image_to_window(vars.mlx, vars.bg_img, 0, 0);
	mlx_image_to_window(vars.mlx, vars.map_img, 0, 0);
	mlx_image_to_window(vars.mlx, vars.player_img,
		vars.p_width * 32, vars.p_height * 32);
	mlx_key_hook(vars.mlx, &key_hook, &vars);
	mlx_loop(vars.mlx);
	exit_and_free(&vars, 0);
	return (0);
}