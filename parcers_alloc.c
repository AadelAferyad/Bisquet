#include "parcer.h"

char	*allocate_map_in_buffer(int fd, int size, int start)
{
	char	*buff;
	int	rbytes;
	int	i;

	i = 0;
	buff = malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (NULL);
	lseek(fd, start - 1, SEEK_SET);
	rbytes = read(fd, buff, size);	
	if (rbytes == -1)
	{
		free(buff);
		printf("Failed reading map");
		return (NULL);
	}
	buff[size] = '\0';
	return (buff);
}

int	allocate_row(int fd, mp *map)
{
	int	i;
	int	h;
	char	*buffer;
	int	j;
	int	size;
	int	row;

	size = (map->columns * map->rows) + (map->rows); 
	i = 0;
	j = 0;
	row = 0;
	h = 0;
	buffer = allocate_map_in_buffer(fd, size, map->rows);
	if (!buffer)
	{
		free(map->av);
		return (0);
	}
	while (i < map->columns)
	{
		map->av[row] = malloc(sizeof(char) * (map->rows + 1));
		if (!map->av[row])
		{
			i = 0;
			while (i < row)
			{
				free(map->av[i]);
				i++;
			}
			free(buffer);
			free(map->av);
			return (0);
		}
		while (j < map->rows + 1 && buffer[h] && buffer[h] != '\n')
		{
			map->av[row][j] = buffer[h];
			j++;
			h++;
		}
		if (buffer[h] == '\n')	
		{
			map->av[row][j + 1] = '\0';
			j = 0;
			h++;
		}
		row++;
		i++;
	}
	free(buffer);
	map->av[row] = NULL;
	return (1);
}

int	allocate_map(int fd, mp *map)
{

	if (!validate_map(fd, map))
	{
		free(map);
		return (0);
	}
	map->av = malloc(sizeof(char *) * (map->columns + 1));
	if (!map->av)
	{
		free(map);
		return (0);
	}
	if (!allocate_row(fd, map))
	{
		free(map);
		return (0);
	}
	return (1);
}
