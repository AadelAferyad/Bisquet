#include "bsq.h"


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
