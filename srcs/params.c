#include "fractol.h"

t_type	set_fractal_type(char *param)
{
	static t_type	type;

	if (type)
		return (type);
	type = Invalid;
	if (ft_strncmp("Julia", param, 6) == 0)
		type = Julia;
	else if (ft_strncmp("Mandelbrot", param, 11) == 0)
		type = Mandelbrot;
	else if (type == Invalid)
		exit_print_instruction(param, NULL);
	return (type);
}

int	set_resolution(char *param)
{
	static int	resolution;
	int			val;

	if (resolution)
		return (resolution);
	val = -1;
	if (param)
	{
		if (ft_strncmp(param, "high", 5) == 0)
			val = 0;
		else if (ft_strncmp(param, "mid", 4) == 0)
			val = 1;
		else if (ft_strncmp(param, "low", 4) == 0)
			val = 2;
	}
	if (val == -1)
		exit_print_instruction(NULL, NULL);
	resolution = pow(2, val) * 10;
	return (resolution);
}

int	set_screen_size(t_mlx *mlx, char *param)
{
	static int	screen_size;
	static int	param_size;
	int			error;
	int			width;
	int			height;

	if (screen_size)
		return (screen_size);
	if (!param_size && param)
	{
		param_size = max(0, ft_atoi_check(param, &error));
		if (error)
			exit_print_instruction(NULL, NULL);
	}
	if (mlx)
	{
		if (!param_size)
			param_size = SCREEN;
		mlx_get_screen_size(mlx->mlx, &width, &height);
		screen_size = min(param_size, min(width, height));
		return (screen_size);
	}
	return (0);
}

void	check_params(int ac, char **av)
{
	int		i;

	if (ac <= 1)
		exit_print_instruction(NULL, NULL);
	set_fractal_type(av[1]);
	i = 2;
	while (av[i])
	{
		if (ft_strncmp(av[i], "-s", 3) == 0)
			set_screen_size(NULL, av[++i]);
		else if (ft_strncmp(av[i], "--screen-size=", 14) == 0)
			set_screen_size(NULL, av[i] + 14);
		else if (ft_strncmp(av[i], "-r", 3) == 0)
			set_resolution(av[++i]);
		else if (ft_strncmp(av[i], "--resolution=", 13) == 0)
			set_resolution(av[i] + 13);
		else
			exit_print_instruction(NULL, av[i]);
		i++;
	}
}
