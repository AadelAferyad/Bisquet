#include "parcer.h"

void	fill_map_fs_line(char *buffer, mp *map)
{
	int len;

	len = ft_strlen(buffer) - 1;
	map->full = buffer[len];
	map->obstacle = buffer[len - 1];
	map->empty = buffer[len - 2];/*12014*/
	buffer[len - 2] = '.';
	map->columns = ft_atoi(buffer);
	map->rows = 0;
}

int	validate_map_fs_line(char *buffer, mp *map)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(buffer) - 1;
	while (buffer[i])
	{
		if (i < 3 && (buffer[len] <= 32 || buffer[len] > 126))
		{
			printf("[invalid map] :The provided characters for (empty, obstacles and full) are non printable characters\n");
			free(map);
			return (0);
		}
		else if (i >= 3 && (len > 4 || !(buffer[len] >= '0' && buffer[len] <= '9'))) 	
		{
			printf("[Invalid map] :The provided number is invalid");
			free(map);
			return (0);
		}
		len--;
		i++;
	}
	fill_map_fs_line(buffer, map);
	return (1);
}

mp	*read_map_fs_line(int fd)
{
	int	i;
	mp	*map;
	char	buffer[READ_SIZE];

	i = 0;
	if (read(fd, buffer, READ_SIZE) == -1)
	{
		printf("failed to read the file");
		return (NULL);
	}
	map = malloc(sizeof(mp));
	if (!map)
		return (NULL);
	while (i < READ_SIZE)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
	if (!validate_map_fs_line(buffer, map))
		return (NULL);
	return (map);
}

int	is_valid(mp *map, char *buffer, int *height, int rbytes)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	while (i < rbytes)
	{
		if (buffer[i] == '\n')
			(*height) = *height + 1;
		else if (*height && map->empty != buffer[i] && map->full != buffer[i] && map->obstacle != buffer[i])
		{
			printf("[Invalid map] map is invalid");
			return (0);
		}
		else if (map->rows && row == map->rows)
		{
			printf("[Invalid map] map is invalid");
			return (0);
		}
		if (*height)
		{
			if (buffer[i] == '\n')
			{
				if (!map->rows)
					map->rows = row;
				row = 0;
			}
			row++;
		}
		i++;
	}
	return (1);
}

int	validate_map(int fd, mp *map)
{
	char	buffer[READ_SIZE];
	int	rbytes;
	int	height;

	height = 0;
	lseek(fd, 0, SEEK_SET);
	//do
	//{
		//rbytes = read(fd, buffer, READ_SIZE);
		//if (rbytes == -1)
		//{
			//printf("Failed reading map");
			//return (0);
		//}
		//if (!rbytes)
			//break;
		//if (rbytes && !is_valid(map, buffer, &height))
			//return (0);	
	//} while (rbytes > 0);
	rbytes = read(fd, buffer, READ_SIZE);
	while (rbytes != 0)
	{
		if (rbytes == -1)
		{
			printf("Failed reading map");
			return (0);
		}
		if (!is_valid(map, buffer, &height, rbytes))
			return (0);	
		rbytes = read(fd, buffer, READ_SIZE);
	}
	if (height - 1 != map->columns)
	{
		printf("[Invalid map] map is invalid\n");
		return (0);
	}
	return (1);
}
