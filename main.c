#include "bsq.h"


int	main(int ac, char **av)
{
	int	i;
	mp	*map;

	i = 1;
	if (ac > 1)
	{
		while (i < ac)	
		{
			map = parcer(av[i]);
			i++;
		}
	}
	return (0);
}
