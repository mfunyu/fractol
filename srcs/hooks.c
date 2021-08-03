#include "fractol.h"

bool	ignore(t_fractal *fractal)
{
	static int	ignore;

	if (ignore++ >= INT_MAX - 1)
		ignore = 0;
	if (fractal->loop > 100 && ignore % (fractal->loop / IGNORE_FREQ))
		return (true);
	return (false);
}

int	key_hook(int key, t_mlx *mlx)
{
	t_fractal	*fr;

	fr = mlx->fractal;
	if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		free_exit(mlx);
	}
	if (key == INFO)
	{
		printf("x: [%f, %f], y: [%f, %f], loop: %d, color: %s\n",
			fr->x_min, fr->x_min + fr->size, fr->y_min, fr->y_min + fr->size,
			fr->loop, t_color_to_char(fr->color));
		return (0);
	}
	if (key == COLOR)
	{
		if (++fr->color == Num_colors)
			fr->color = 0;
	}
	else if (key == RESET)
		init_t_fractal(fr, mlx);
	put_fractal(mlx);
	return (0);
}

int	key_press(int key, t_mlx *mlx)
{
	t_fractal	*fr;

	fr = mlx->fractal;
	if (ignore(mlx->fractal))
		return (0);
	if (key == INC || key == DEC)
	{
		if (key == INC)
		{
			fr->loop += 4;
			ft_putendl_fd("increasing loops ...", STDOUT_FILENO);
		}
		else
		{
			if (fr->loop == LOOP_MIN)
				return (0);
			fr->loop = max(LOOP_MIN, fr->loop - 4);
			ft_putendl_fd("decreasing loops ...", STDOUT_FILENO);
		}
		put_fractal(mlx);
		ft_putendl_fd(CLEAR_SCREEN, STDOUT_FILENO);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	if (ignore(mlx->fractal))
		return (0);
	if (button == UP || button == DOWN)
	{
		if (button == UP)
		{
			set_zoom(mlx->fractal, x, y, 1);
			ft_putendl_fd("zooming in ...", STDOUT_FILENO);
			mlx->fractal->loop = max(mlx->fractal->loop,
					calc_loop(mlx->fractal));
		}
		if (button == DOWN)
		{
			set_zoom(mlx->fractal, x, y, -1);
			ft_putendl_fd("zooming out ...", STDOUT_FILENO);
			mlx->fractal->loop = min(mlx->fractal->loop,
					calc_loop(mlx->fractal));
		}
	}
	put_fractal(mlx);
	ft_putendl_fd(CLEAR_SCREEN, STDOUT_FILENO);
	return (0);
}
