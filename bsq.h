#ifndef FT_BSQ
#define FT_BSQ

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdio.h>

struct mapper
{
	int	rows;
	int	columns;
	char	empty;
	char	full;
	char	obstacle;
	int	x;
	int	y;
	int	area;
	char	**av;
};
typedef struct mapper map;

int	ft_atoi(char *str);

#endif