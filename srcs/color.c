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

int	*convert_to_rgb(int val, int set_max, int set_min, int change)
{
	int		*color;
	double	S;
	double	V;
	int		max;
	int		min;

	color = (int *)malloc(sizeof(int) * 4);
	S = 200;
	V = 255;
	max = V;
	min = max - ((S / 255) * max);
	color[set_max] = max;
	color[set_min] = min;
	color[change] = val / 60 * (max - min) + min;
	return (color);
}

int	set_gradation_color(int H)
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
