#include "fractol.h"

int	julia_set(double x, double y, t_fractal *frac)
{
	double	zx;
	double	zy;
	double	save_x;
	int		n;

	zx = frac->x_min + x / WIDTH * frac->x_size;
	zy = frac->y_min + y / HEIGHT * frac->y_size;
	n = 0;
	while (n < frac->loop)
	{
		if (zx * zx + zy * zy < -DIVERGE || zx * zx + zy * zy > DIVERGE)
			return (n);
		save_x = zx;
		zx = zx * zx - zy * zy + frac->c_real;
		zy = 2 * save_x * zy + frac->c_imag;
		n++;
	}
	return (0);
}
