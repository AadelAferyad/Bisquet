#include "bsq.h"


map	*fill_the_map(map *mmap, char *path)
{
	int	fd;
	int	rd;
	int	i;
	char 	buff[2];
	int	j;

	j = 0;
	rd = 1;
	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (rd)
	{
		rd = read(fd, buff, 1);
		if (*buff == '\n')
		{
			break;
		}
	}
	while (i < mmap->columns)
	{
		//if (!i)
		//	lseek(fd, mmap->rows, SEEK_CUR);
		rd = read(fd, mmap->av[i], mmap->rows);
		if (rd == -1)
			return (NULL);
		mmap->av[i][mmap->rows] = '\0';
		i++;
	}
	mmap->av[i] = NULL;
	return (mmap);
}



map	*find_square(map *mmap)
{
	int	i;

	i = 0;
	mmap->av = malloc(sizeof(char *) * (mmap->columns + 1));
	if (!mmap->av)
		return (NULL);
	while (i < mmap->columns)
	{
		mmap->av[i] = malloc(sizeof(char) * (mmap->rows + 1));
		if (!mmap->av[i])
		{
			while (i > 0)
			{
				free(mmap->av[i - 1]);
				i--;
			}
			free(mmap->av);
			return (NULL);
		}
		i++;
	}
	mmap->av[i] = NULL;
	return (mmap);
}


int	is_valid_map(char f, char b, char e)
{
	if (f == b || f == e || b == e)
		return (1);
	return (0);
}

map	*ft_read_map(char *s)
{
	map *fmap;
	int fd;
	int rd = 1;
	int i = 0;
	char buff[500];
	int columns = 0, rows = 0;

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
			fmap->rows = 0;
			if (fmap->columns <= 0 || is_valid_map(fmap->full, fmap->obstacle, fmap->empty))
			{
				free(fmap);
				printf("some errors\n");
				return (NULL);
			}
			i = 0;
			continue ;
		}
		if (fmap->columns && buff[i] != '\n' && buff[i] != fmap->empty && buff[i] != fmap->obstacle)
		{
				printf("not the same character %c %c %c\n", fmap->empty, fmap->obstacle,rows);
				free(fmap);
				return (NULL);
		}
		if (buff[i] == '\n' && fmap->columns)
		{
			if (!fmap->rows)
			{
				fmap->rows = i + 1;
				rows = fmap->rows - 1;
			}
			if (rows + 1 != fmap->rows)
			{
				printf("not the same length rows width %d %d\n", fmap->rows, rows);
				free(fmap);
				return (NULL);
			}
			rows = 0;
			i = 0;
			columns++;
			continue ; 
		}
		if (fmap->rows)
			rows++;
		i++;
	}
	if (fmap->columns != columns)
	{

		free(fmap);
		printf("not the same height\n");
		return (NULL);
	}
	return (fmap);
}

int	main(int ac, char **av)
{
	int	i;
	map	*mmap;
	int	j;

	j = 0;
	i = 1;
	if (ac > 1)
	{
		while (i < ac)
		{
			j = 0;
			mmap = ft_read_map(av[i]);
			if (!mmap)
				return (-1);
			if (find_square(mmap))
				fill_the_map(mmap, av[i]);
			i++;
			while (j < mmap->columns)
			{
				free(mmap->av[j]);
				j++;
			}
			free(mmap->av);
			free(mmap);
		}
	}
	return (0);
}
