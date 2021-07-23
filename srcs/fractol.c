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

void	set_zoom(t_fractal *fractal, int x_ptr, int y_ptr)
{
	double	x_dif;
	double	y_dif;
	double	x_pixel;
	double	y_pixel;

	x_dif = x_ptr - WIDTH / 2;
	y_dif = y_ptr - HEIGHT / 2;
	x_pixel = (fractal->x_max - fractal->x_min) / WIDTH;
	y_pixel = (fractal->y_max - fractal->y_min) / WIDTH;
	if (fractal->zoom == 1)
	{
		if (x_dif < 0)
			shift_range(&fractal->x_max, &fractal->x_min, -x_dif, -x_pixel);
		else
			shift_range(&fractal->x_min, &fractal->x_max, x_dif, x_pixel);
		if (y_dif < 0)
			shift_range(&fractal->y_max, &fractal->y_min, -y_dif, -y_pixel);
		else
			shift_range(&fractal->y_min, &fractal->y_max, y_dif, y_pixel);
	}
	else if (fractal->zoom == -1)
	{
		if (x_dif < 0)
			shift_range(&fractal->x_min, &fractal->x_max, -x_dif, -x_pixel);
		else
			shift_range(&fractal->x_max, &fractal->x_min, x_dif, x_pixel);
		if (y_dif < 0)
			shift_range(&fractal->y_min, &fractal->y_max, -y_dif, -y_pixel);
		else
		shift_range(&fractal->y_max, &fractal->y_min, y_dif, y_pixel);
	}
	// x_mid = x_min + x_ptr * x_pixel;
	// fractal->x_max = fractal->x_max - (fractal->zoom * x_pixel * ZOOM_SPEED);
	// fractal->x_min = fractal->x_min + (fractal->zoom * x_pixel * ZOOM_SPEED);
	// fractal->y_max = fractal->y_max - (fractal->zoom * y_pixel * ZOOM_SPEED);
	// fractal->y_min = fractal->y_min + (fractal->zoom * y_pixel * ZOOM_SPEED);
}

int	zoom(int button, int x, int y, t_mlx *mlx)
{
	DI(x);
	DI(y);
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
