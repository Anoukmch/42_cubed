#include "../includes/cub3d.h"

int	check_extension(char *mapfile)
{
	int	len;
	int	fd;

	len = ft_strlen(mapfile);
	fd = open(mapfile, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ft_putstr_fd("Error\nPath is a directory\n", 2);
		exit(1);
	}
	close(fd);
	if (!(mapfile[len - 4] == '.' && mapfile[len - 3] == 'c'
			&& mapfile[len - 2] == 'u' && mapfile[len - 1] == 'b'))
	{
		ft_putstr_fd("Error\nWrong input file\n", 2);
		exit(1);
	}
	return (1);
}
