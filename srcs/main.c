#include "fractol.h"

t_type	fractal_type(char *param)
{
	if (ft_strncmp("Julia", param, 6) == 0)
		return (Julia);
	if (ft_strncmp("Mandelbrot", param, 11) == 0)
		return (Mandelbrot);
	return (-1);
}

void	init_t_mlx(t_mlx *mlx, char **av)
{
	int		width;
	int		height;
	int		error;
	int		size;

	mlx->mlx = mlx_init();
	mlx->screen = SCREEN;
	if (av[2])
	{
		size = ft_atoi_check(av[2], &error);
		if (!error)
		{
			mlx_get_screen_size(mlx->mlx, &width, &height);
			mlx->screen = min(size, min(width, height));
			DI(mlx->screen);
		}
	}
	mlx->window = mlx_new_window(mlx->mlx, mlx->screen, mlx->screen, av[1]);
	if (!mlx->window)
		error_exit("mlx window");
	DI(mlx->screen);
}

void	init_t_fractal(t_fractal *fractal, t_type type, t_mlx *mlx)
{
	fractal->screen = mlx->screen;
	fractal->type = type;
	fractal->x_min = MIN;
	fractal->y_min = MIN;
	fractal->size = SIZE;
	fractal->c_real = C_REAL;
	fractal->c_imag = C_IMAG;
	fractal->color = 1;
	fractal->loop = max(10,
			50.0 * pow(log(fractal->screen / fractal->size), 1.25));
	mlx->fractal = fractal;
}

void	start_mlx_loop(t_mlx *mlx)
{
	mlx_key_hook(mlx->window, key_hook, mlx);
	mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_hook(mlx->window, DestroyNotify, StructureNotifyMask, free_exit, mlx);
	mlx_hook(mlx->window, KeyPress, KeyPressMask, key_press, mlx);
	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_type		type;
	t_mlx		mlx;
	t_fractal	frac;

	if (ac <= 1)
		exit_print_instruction(av[1]);
	type = fractal_type(av[1]);
	if (type < 0)
		exit_print_instruction(av[1]);
	init_t_mlx(&mlx, av);
	init_t_fractal(&frac, type, &mlx);
	put_fractal(&mlx);
	start_mlx_loop(&mlx);
	return (0);
}
