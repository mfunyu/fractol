#include "fractol.h"

int	mandelbrot_set(double x, double y, t_fractal *frac)
{
	double	zx;
	double	zy;
	double	save_x;
	int		n;

	x = x / (WIDTH / (frac->x_max - frac->x_min)) + frac->x_min;
	y = y / (HEIGHT / (frac->y_max - frac->y_min)) + frac->y_min;
	zx = 0;
	zy = 0;
	n = -1;
	while (++n < frac->loop)
	{
		if (sqrt(zx * zx + zy * zy) > DIVERGE)
			return (n);
		save_x = zx;
		zx = zx * zx - zy * zy + x;
		zy = 2 * save_x * zy + y;
	}
	return (0);
}
