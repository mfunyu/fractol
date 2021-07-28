#include "fractol.h"

bool	skip(t_fractal *fractal)
{
	static int	skip;

	if (skip++ >= INT_MAX - 1)
		skip = 0;
	if (fractal->loop > 100 && skip % (fractal->loop / IGNORE_FREQ))
		return (true);
	return (false);
}

int	key_hook(int key, t_mlx *mlx)
{
	t_fractal	*fr;

	fr = mlx->fractal;
	DI(key);
	if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		free_exit(mlx);
	}
	if (key == RANGE)
		printf("x: [%f, %f], y: [%f, %f]\n", fr->x_min, fr->x_min + fr->size,
			fr->y_min, fr->y_min + fr->size);
	else
	{
		if (key == RESET)
			init_t_fractal(fr, fr->type, mlx);
		if (key == INC)
			fr->loop += 4;
		if (key == DEC)
			fr->loop = max(10, fr->loop - 4);
		put_fractal(mlx);
	}
	return (0);
}

int	key_press(int key, t_mlx *mlx)
{
	t_fractal	*fr;

	fr = mlx->fractal;
	if (skip(mlx->fractal))
		return (0);
	if (key == INC || key == DEC)
	{
		if (key == INC)
		{
			fr->loop += 4;
			ft_putendl_fd("zooming in ...", STDOUT_FILENO);
		}
		else
		{
			if (fr->loop == 10)
				return (0);
			fr->loop = max(10, fr->loop - 4);
			ft_putendl_fd("zooming out ...", STDOUT_FILENO);
		}
		put_fractal(mlx);
		ft_putendl_fd(CLEAR_SCREEN, STDOUT_FILENO);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	if (skip(mlx->fractal))
		return (0);
	if (button == UP || button == DOWN)
	{
		if (button == UP)
		{
			set_zoom(mlx->fractal, x, y, 1);
			ft_putendl_fd("zooming in ...", STDOUT_FILENO);
		}
		if (button == DOWN)
		{
			set_zoom(mlx->fractal, x, y, -1);
			ft_putendl_fd("zooming out ...", STDOUT_FILENO);
		}
		mlx->fractal->loop = max(10,
				50.0 * pow(log(mlx->screen / mlx->fractal->size), 1.25));
		DI(mlx->fractal->loop);
	}
	put_fractal(mlx);
	ft_putendl_fd(CLEAR_SCREEN, STDOUT_FILENO);
	return (0);
}
