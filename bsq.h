#ifndef FT_BSQ
#define FT_BSQ

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdio.h>

#define READ_SIZE 1024

struct m_map
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
typedef struct m_map mp;

int	ft_atoi(char *str);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *src, char *dest);
mp	*parcer(char *file_name);
int	ft_strlen(char *str);
#endif
