#include "bsq.h"


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	n;
	int	i;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n * sign);
}

char	*ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


void	ft_collector(mp *map)
{
	int	i;

	i = 0;
	while (i < map->columns)
	{
		free(map->av[i]);
		i++;
	}
	free(map->av);
	free(map);
}

void	ft_print_map(mp *map)
{
	int	i;
	
	i = 0;
	while (i < map->columns)
	{
		printf("%s\n", map->av[i]);
		i++;
	}
}







