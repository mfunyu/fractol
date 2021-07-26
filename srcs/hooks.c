#include "fractol.h"

int	key_hook(int key, t_mlx *mlx)
{
	DI(key);
	if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		free_exit(mlx);
	}
	if (key == RESET)
	{
		init_t_fractal(mlx->fractal);
		put_mandelbrot(mlx);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	static int	skip;

	if (skip >= INT_MAX - 1)
		skip = 0;
	skip++;
	if (skip % IGNORE_FREQ)
		return (0);
	if (button == UP)
	{
		mlx->fractal->zoom = 1;
		mlx->fractal->loop = log(5 * exp(mlx->fractal->loop));
		// mlx->fractal->loop += 4;
	}
	if (button == DOWN)
	{
		mlx->fractal->zoom = -1;
		// mlx->fractal->loop -= 4;
		mlx->fractal->loop = log(0.8 * exp(mlx->fractal->loop));
	}
	DI((int)mlx->fractal->loop);
	set_zoom(mlx->fractal, x, y);
	put_mandelbrot(mlx);
	return (0);
}
