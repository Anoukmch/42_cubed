#include "../includes/cub3d.h"

void	ft_init_textures(t_vars *vars)
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
	vars->textures[WALL_DOWN] = mlx_load_png("./pngfiles/walldown.png");
	vars->textures[WALL_UP] = mlx_load_png("./pngfiles/wallup.png");
	vars->textures[COLLECTS] = mlx_load_png("./pngfiles/collectible.png");
	vars->textures[EXIT] = mlx_load_png("./pngfiles/exit.png");
	vars->textures[BOX] = mlx_load_png("./pngfiles/box.png");
	i = 0;
	while (i < TEXTURES)
	{
		if (vars->textures[i] == NULL)
		{
			printf("Please check the initialization of your textures!\n");
			exit_and_free(vars, 1);
		}
		i++;
	}
}

void	check_texturesize(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (vars->textures[i]->height != 32 || vars->textures[i]->width != 32)
		{
			printf("Please check the sizes of your textures!\n");
			exit_and_free(vars, 1);
		}
		i++;
	}
}

int	countinglines(char **argv)
{
	int		reading;
	int		counter;
	char	*gnl;

	counter = 0;
	reading = open(argv[1], O_RDONLY);
	if (reading == -1)
	{
		perror(argv[1]);
		exit (1);
	}
	while (1)
	{
		gnl = get_next_line(reading);
		if (gnl == NULL)
			break ;
		free (gnl);
		counter++;
	}
	close(reading);
	if (counter == 0)
		ft_printf("Map error: Empty file!\n");
	if (counter == 0)
		exit (1);
	return (counter);
}

void	readingmap(char **argv, t_vars *vars)
{
	int		linenumbers;
	int		counter;
	int		reading;

	counter = 0;
	linenumbers = countinglines(argv);
	vars->map = (char **)malloc(linenumbers * sizeof(char *));
	if (vars->map == NULL)
		exit (1);
	reading = open(argv[1], O_RDONLY);
	if (reading == -1)
		perror(argv[1]);
	if (reading == -1)
		exit_and_free(vars, 1);
	while (counter < linenumbers)
	{
		vars->map[counter] = get_next_line(reading);
		if (vars->map[counter] == NULL)
			break ;
		counter++;
	}
	close(reading);
	vars->m_height = linenumbers;
	vars->m_width = ft_strlen(vars->map[0]) - 1;
	set_player_pos(vars);
}

void	set_player_pos(t_vars *vars)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (h < vars->m_height)
	{
		while (w < vars->m_width)
		{
			errorhandling(vars, w, h);
			if (vars->map[h][w] == 'P')
			{
				vars->p_width = w;
				vars->p_height = h;
			}
			w++;
		}
		w = 0;
		h++;
	}
	if (vars->exit_no < 1 || vars->player_no != 1 || vars->coll_no < 1)
	{
		ft_printf("Map error: Please check the number of characters!\n");
		exit_and_free(vars, 1);
	}
}
