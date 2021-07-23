#include "fractol.h"

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
		mlx->fractal->zoom = 1;
	if (button == DOWN)
		mlx->fractal->zoom = -1;
	set_zoom(mlx->fractal, x, y);
	put_mandelbrot(mlx, mlx->fractal);
	return (0);
}
