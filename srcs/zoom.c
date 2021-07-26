#include "fractol.h"

void	update_loop(t_fractal *fractal)
{
	double	loop_size;

	// loop_size = (X_MAX - X_MIN) / (fractal->x_max - fractal->x_min) + LOOP;
	loop_size = pow(10 / (fractal->x_max - fractal->x_min), 2) / (X_MAX - X_MIN) + LOOP;
	// loop_size *= (fractal)
	fractal->loop = (int)loop_size;
}

double	set_new_size(t_fractal *fractal, double size_per_px, bool x)
{
	double	old_size;
	double	change_size;
	double	new_size;
	// static int l;

	if (x)
		old_size = fractal->x_max - fractal->x_min;
	else
		old_size = fractal->y_max - fractal->y_min;
	change_size = ZOOM_SPEED * size_per_px * fractal->zoom;
	new_size = old_size - change_size;
	// if (l % 10 == 0)
	// 	fractal->loop += 1;
	// l++;
	return (new_size);
}

void	set_zoom(t_fractal *fractal, int x_fix, int y_fix)
{
	double	x_size_per_px;
	double	y_size_per_px;
	double	new_x_size;
	double	new_y_size;

	x_size_per_px = (fractal->x_max - fractal->x_min) / WIDTH;
	y_size_per_px = (fractal->y_max - fractal->y_min) / HEIGHT;
	new_x_size = set_new_size(fractal, x_size_per_px, true);
	new_y_size = set_new_size(fractal, y_size_per_px, false);
	fractal->x_min += x_fix * x_size_per_px - new_x_size * x_fix / WIDTH;
	fractal->x_max = fractal->x_min + new_x_size;
	fractal->y_min += y_fix * y_size_per_px - new_y_size * y_fix / HEIGHT;
	fractal->y_max = fractal->y_min + new_y_size;
	// update_loop(fractal);
}
