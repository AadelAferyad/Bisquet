#include "bsq.h"

map	*ft_read_map(char *s)
{
	map *fmap;
	int fd;
	int rd = 1;
	int i = 0;
	char buff[500];

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (NULL);
	fmap = malloc(sizeof(map));
	if (!fmap)
		return (NULL);
	fmap->columns = 0;
	while (rd > 0)
	{
		rd = read(fd, &buff[i], 1); 
		if (rd == -1)
			return (NULL);
		if (buff[i] == '\n' && !fmap->columns)
		{
			fmap->full = buff[--i];
			fmap->obstacle = buff[--i];
			fmap->empty = buff[--i];
			buff[i] = '~';
			fmap->columns = ft_atoi(buff);
			if (!fmap->columns)
			{
				free(fmap);
				return (NULL);
			}
		}
		i++;
	}
	return (fmap);
}

int	main(int ac, char **av)
{
	int	i;
	map	*mmap;

	i = 1;
	if (ac > 1)
	{
		while (i < ac)
		{
			mmap = ft_read_map(av[i]);
			if (!mmap)
				return (-1);
			printf("%d\n%c\n%c\n%c\n", mmap->columns, mmap->empty, mmap->obstacle, mmap->full);
			i++;
			free(mmap);
		}
	}
	return (0);
}
