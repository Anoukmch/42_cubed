#include "../includes/cub3d.h"

// NEW LINES AFTER MAP IS OK --> CHECK THAT

void	check_restoffile(t_map *map)
{
	int read;
	int	count;
	char *tmp;
	int	i;

	read = open(map->m_argv, O_RDONLY);
	count = 0;
	if (read == -1)
		exit (printf("reading map = impossible!\n"));
	while (count < map->mapstart)
	{
		tmp = get_next_line(read);
		free (tmp);
		count++;
	}
	count = 0;
	i = map->maplines;
	while (count <= i)
	{
		tmp = get_next_line(read);
		count++;
	}
}

char	*ft_free_strtrim(char *s1, char const *set)
{
	size_t	len;
	char	*final;

	if (set == 0 || s1 == 0)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
	}
	len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[len]))
	{
		len--;
	}
	final = ft_substr(s1, 0, len + 1);
	free (s1);
	return (final);
}

void	checkemptylines(t_map *map, char *lastline)
{
	char	*gnl;
	int		i;

	i = 0;
	gnl = lastline;
	while (1)
	{
		while (gnl[i] == ' ' || gnl[i] == '\t')
			i++;
		if (gnl[i] == '\n')
		{
			map->mapstart++;
			gnl = get_next_line(map->fd);
			i = 0;
		}
		else
			break ;
	}
}

void	countinglines(t_map *map, char *lastline)
{
	char	*gnl;

	checkemptylines(map, lastline);
	while (1)
	{
		gnl = get_next_line(map->fd);
		if (!ft_strcmp(gnl, "\n"))
			break ;
		if (gnl == NULL)
			break ;
		free (gnl);
		map->maplines++;
	}
	while (gnl)
	{
		gnl = get_next_line(map->fd);
		if (ft_strcmp(gnl, "\n\n"))
			exit(printf("ERROR BECAUSE OF OTHER THINGS AFTER MAP\n"));
	}
	close(map->fd);
	if (!map->maplines)
		exit (printf("Map error: No existing map!\n"));
}

void	getmap_content(t_map *map)
{
	int		count;
	int		read;
	char	*tmp;

	count = 0;
	check_restoffile(map);
	map->cmap = malloc((map->maplines + 2) * sizeof(char *));
	if (!map->cmap)
		exit (printf("allocation error\n"));
	read = open(map->m_argv, O_RDONLY);
	if (read == -1)
		exit (printf("reading map = impossible!\n"));
	while (count < map->mapstart)
	{
		tmp = get_next_line(read);
		free (tmp);
		count++;
	}
	count = 0;
	while (count <= map->maplines)
	{
		map->cmap[count] = get_next_line(read);
		count++;
	}
	map->cmap[count] = NULL;
	close (read);
}

void get_finalmap(t_map *map, char *lastline)
{
	int	i;

	i = 0;
	countinglines(map, lastline);
	getmap_content(map);
	while (map->cmap[i])
	{
		map->cmap[i] = ft_free_strtrim(map->cmap[i], "\n");
		i++;
	}
}