#include "fractol.h"

int	set_resolution(int ac, char **av)
{
	int		i;
	int		val;

	val = 0;
	if (ac >= 3)
	{
		i = 2;
		while (av[i])
		{
			if (ft_strncmp(av[i], "high", 5) == 0)
				val = 0;
			else if (ft_strncmp(av[i], "mid", 4) == 0)
				val = 1;
			else if (ft_strncmp(av[i], "low", 4) == 0)
				val = 2;
			else
			{
				i++;
				continue ;
			}
			break ;
		}
	}
	return (pow(2, val) * 10);
}
