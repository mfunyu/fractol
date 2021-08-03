#include "fractol.h"

int	mandelbrot_set(double x, double y, t_fractal *frac)
{
	double	zx;
	double	zy;
	double	save_x;
	int		n;

	x = frac->x_min + x / frac->screen * frac->size;
	y = frac->y_min + y / frac->screen * frac->size;
	zx = 0;
	zy = 0;
	n = 1;
	while (n <= frac->loop)
	{
		if (zx * zx + zy * zy < -DIVERGE || zx * zx + zy * zy > DIVERGE)
			return (n);
		save_x = zx;
		zx = zx * zx - zy * zy + x;
		zy = 2 * save_x * zy + y;
		n++;
	}
	return (0);
}
