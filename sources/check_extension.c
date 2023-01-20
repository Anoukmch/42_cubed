
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
		return (0);
	}
	close(fd);
	if (!(mapfile[len - 4] == '.' && mapfile[len - 3] == 'c'
			&& mapfile[len - 2] == 'u' && mapfile[len - 1] == 'b'))
		return (0);
	return (1);
}
