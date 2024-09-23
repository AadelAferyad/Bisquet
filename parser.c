#include "parcer.h"


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
	if (!allocate_map(fd, map))
		return (NULL);
	return (map);
}
