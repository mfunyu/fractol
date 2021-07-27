#include "fractol.h"

double	set_new_size(t_fractal *fractal, double old_px_size, bool x)
{
	double	size_diff;
	double	new_size;

	size_diff = ZOOM_SPEED * old_px_size;
	if (x)
		new_size = fractal->x_size - size_diff;
	else
		new_size = fractal->y_size - size_diff;
	return (new_size);
}

void	set_zoom(t_fractal *fractal, int x_fix, int y_fix, int zoom_dir)
{
	double	old_x_px_size;
	double	old_y_px_size;

	old_x_px_size = fractal->x_size / WIDTH;
	old_y_px_size = fractal->y_size / HEIGHT;
	fractal->x_size = set_new_size(fractal, zoom_dir * old_x_px_size, true);
	fractal->y_size = set_new_size(fractal, zoom_dir * old_y_px_size, false);
	fractal->x_min += x_fix * (old_x_px_size - fractal->x_size / WIDTH);
	fractal->y_min += y_fix * (old_y_px_size - fractal->y_size / HEIGHT);
}
