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
			if (map)
			{
				ft_print_map(map);
				ft_collector(map);
			}		
			i++;
		}
	}
	return (0);
}
