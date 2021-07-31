#include "fractol.h"

int	calc_loop(t_fractal *fractal)
{
	return (max(LOOP_MIN, 50.0 * pow(log10(fractal->screen
					/ fractal->size / fractal->resolution), 1.25)));
}

double	set_new_size(t_fractal *fractal, double old_px_size)
{
	double	size_diff;
	double	new_size;

	size_diff = ZOOM_SPEED * old_px_size;
	new_size = fractal->size - size_diff;
	return (new_size);
}

void	set_zoom(t_fractal *fractal, int x_fix, int y_fix, int zoom_dir)
{
	double	old_px_size;

	old_px_size = fractal->size / fractal->screen;
	fractal->size = set_new_size(fractal, zoom_dir * old_px_size);
	fractal->x_min += x_fix * (old_px_size - fractal->size / fractal->screen);
	fractal->y_min += y_fix * (old_px_size - fractal->size / fractal->screen);
}
