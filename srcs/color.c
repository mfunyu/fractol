#include "fractol.h"

int	calc_rgb(int *color_vec)
{
	long long	color;

	color = color_vec[0] << 16;
	color += color_vec[1] << 8;
	color += color_vec[2];
	null_free((void **)&color_vec);
	return (color);
}

int	*convert_to_rgb(double val, int set_max, int set_min, int change)
{
	int		*color;
	double	S;
	double	V;
	double	max;
	double	min;

	color = (int *)malloc(sizeof(int) * 4);
	S = 200;
	V = 255;
	max = V;
	min = max - ((S / 255) * max);
	color[set_max] = (int)max;
	color[set_min] = (int)min;
	color[change] = (int)(val / 60.0 * (max - min) + min);
	return (color);
}

int	set_gradation_color(double H)
{
	int		*color;

	if (0 <= H && H <= 60)
		color = convert_to_rgb(H, R, B, G);
	if (60 < H && H <= 120)
		color = convert_to_rgb(120 - H, G, B, R);
	if (120 < H && H <= 180)
		color = convert_to_rgb(H - 120, G, R, B);
	if (180 < H && H <= 240)
		color = convert_to_rgb(240 - H, B, R, G);
	if (240 < H && H <= 300)
		color = convert_to_rgb(H - 240, B, G, R);
	if (300 < H && H <= 360)
		color = convert_to_rgb(360 - H, R, G, B);
	return (calc_rgb(color));
}

char	*t_color_to_char(t_color color)
{
	if (color == Gradation)
		return ("gradation");
	else if (color == Reverse)
		return ("reverse");
	else if (color == Blue)
		return ("blue");
	else if (color == Monochrome)
		return ("monochrome");
	return (NULL);
}

int	set_color(t_fractal *fractal, int n)
{
	if (fractal->color == Gradation)
		return (set_gradation_color(n * 360.0 / fractal->loop));
	else if (fractal->color == Reverse)
		return (set_gradation_color((fractal->loop - n)
				* 360.0 / fractal->loop));
	else if (fractal->color == Blue)
		return (set_gradation_color((n / 2 + fractal->loop / 2)
				* 360.0 / fractal->loop));
	else if (fractal->color == Monochrome)
		return (n % 2 * (int)(0xFFFFFFFF));
	return (0);
}
