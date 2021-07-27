#include "fractol.h"

bool	is_valid_parameter(char *param)
{
	if (ft_strncmp("Julia", param, 6) == 0)
		return (true);
	if (ft_strncmp("Mandelbrot", param, 11) == 0)
		return (true);
	return (false);
}

void	init_t_mlx(t_mlx *mlx, char *name, t_fractal *fractal)
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, name);
	mlx->fractal = fractal;
}

void	init_t_fractal(t_fractal *fractal)
{
	fractal->x_min = MIN;
	fractal->y_min = MIN;
	fractal->x_size = SIZE;
	fractal->y_size = (double)SIZE / WIDTH * HEIGHT;
	fractal->loop = max(10,
			50.0 * pow(log(WIDTH / fractal->x_size), 1.25));
}

void	start_mlx_loop(t_mlx *mlx)
{
	mlx_key_hook(mlx->window, key_hook, mlx);
	mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_hook(mlx->window, DESTROY_NOTIFY,
		STRUCTURE_NOTIFY_MASK, free_exit, mlx);
	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_fractal	frac;

	if (ac <= 1 || !is_valid_parameter(av[1]))
		exit_print_instruction(av[1]);
	init_t_fractal(&frac);
	init_t_mlx(&mlx, av[1], &frac);
	put_fractal(&mlx);
	start_mlx_loop(&mlx);
	return (0);
}
