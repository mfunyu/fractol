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
	fractal->x_max = X_MAX;
	fractal->x_min = X_MIN;
	fractal->y_max = Y_MAX;
	fractal->y_min = Y_MIN;
	fractal->zoom = 0;
}

void	shift_range(double *outer, double *inner, double diff, double px_size)
{
	if (diff < ZOOM_SPEED)
	{
		*outer = *outer + px_size * (ZOOM_SPEED + diff);
		*inner = *inner - px_size * (ZOOM_SPEED - diff);
	}
	else
		*outer = *outer + px_size * (ZOOM_SPEED * 2);
}

double	set_new_size(t_fractal *fractal, double size_per_px, bool x)
{
	double	old_size;
	double	change_size;
	double	new_size;

	if (x)
		old_size = fractal->x_max - fractal->x_min;
	else
		old_size = fractal->y_max - fractal->y_min;
	change_size = ZOOM_SPEED * size_per_px * fractal->zoom;
	new_size = old_size - change_size;
	return (new_size);
}

void	set_zoom(t_fractal *fractal, int x_fix, int y_fix)
{
	double	x_size_per_px;
	double	y_size_per_px;
	double	new_x_size;
	double	new_y_size;

	x_size_per_px = (fractal->x_max - fractal->x_min) / WIDTH;
	y_size_per_px = (fractal->y_max - fractal->y_min) / WIDTH;
	new_x_size = set_new_size(fractal, x_size_per_px, true);
	new_y_size = set_new_size(fractal, y_size_per_px, false);
	fractal->x_min += x_fix * x_size_per_px - new_x_size * x_fix / WIDTH;
	fractal->x_max = fractal->x_min + new_x_size;
	fractal->y_min += y_fix * y_size_per_px - new_y_size * y_fix / HEIGHT;
	fractal->y_max = fractal->y_min + new_y_size;
}

int	zoom(int button, int x, int y, t_mlx *mlx)
{
	if (button == UP)
	{
		mlx->fractal->zoom = 1;
	}
	if (button == DOWN)
	{
		mlx->fractal->zoom = -1;
	}
	set_zoom(mlx->fractal, x, y);
	put_mandelbrot(mlx, mlx->fractal);
	return (0);
}

void	start_mlx_loop(t_mlx *mlx)
{
	mlx_key_hook(mlx->window, key_hook, mlx);
	mlx_mouse_hook(mlx->window, zoom, mlx);
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
	put_mandelbrot(&mlx, &frac);
	start_mlx_loop(&mlx);
	return (0);
}
