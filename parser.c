#include "bsq.h"

void	fill_map_fs_line(char *buffer, mp *map)
{
	int len;

	len = ft_strlen(buffer) - 1;
	map->full = buffer[len];
	map->obstacle = buffer[len - 1];
	map->empty = buffer[len - 2];/*12014*/
	buffer[len - 2] = '.';
	map->columns = ft_atoi(buffer);
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
int	validate_map(int fd, mp *map)
{
	char	buffer[READ_SIZE];
	int	rbytes;

	lseek(fd, 0, SEEK_SET);
	do
	{

		rbytes = read(fd, buffer, READ_SIZE);
	} while (rbytes > 0)
}

char	**allocate_map(int fd, mp *map)
{
	char	**map;

	if (!validate_map(fd, map))
		return (NULL);
	printf("%s %d tests\n", buffer, ft_strlen(buffer));
	return (NULL);
}

mp	*parcer(char *file_name)
{
	int	fd;
	int	i;
	mp	*map;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("error opening the file\n");
		return (NULL);
	}
	map = read_map_fs_line(fd);
	if (!map)
		return (NULL);
	map->av = allocate_map(fd);	
	return (map);
}
