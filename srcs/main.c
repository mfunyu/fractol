#include "fractol.h"

t_type	fractal_type(char *param)
{
	if (ft_strncmp("Julia", param, 6) == 0)
		return (Julia);
	if (ft_strncmp("Mandelbrot", param, 11) == 0)
		return (Mandelbrot);
	return (-1);
}

void	init_t_mlx(t_mlx *mlx, char *name, t_fractal *fractal)
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, name);
	mlx->fractal = fractal;
}

void	init_t_fractal(t_fractal *fractal, t_type type)
{
	fractal->type = type;
	fractal->x_min = MIN;
	fractal->y_min = MIN;
	fractal->x_size = SIZE;
	fractal->y_size = (double)SIZE / WIDTH * HEIGHT;
	fractal->c_real = C_REAL;
	fractal->c_imag = C_IMAG;
	fractal->loop = max(10,
			50.0 * pow(log(WIDTH / fractal->x_size), 1.25));
}

void	start_mlx_loop(t_mlx *mlx)
{
	mlx_key_hook(mlx->window, key_hook, mlx);
	mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_hook(mlx->window, DestroyNotify,
		StructureNotifyMask, free_exit, mlx);
	mlx_hook(mlx->window, KeyPress,
		KeyPressMask, key_press, mlx);
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
	init_t_fractal(&frac, type);
	init_t_mlx(&mlx, av[1], &frac);
	put_fractal(&mlx);
	start_mlx_loop(&mlx);
	return (0);
}
