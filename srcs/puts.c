#include "fractol.h"

void	mlx_pixel_put_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + x * (img->bpp / 8) + (y * img->line_len);
	*(unsigned int *)dst = color;
}

void	init_t_img(t_img *img, t_mlx *mlx)
{
	img->image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->image, &img->bpp, &img->line_len,
			&img->endian);
}

void	put_julia(t_mlx *mlx)
{
	int		x;
	int		y;
	t_img	img;

	init_t_img(&img, mlx);
	y = 0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			mlx_pixel_put_to_img(&img, x, y, 200);
			x++;
		}
		y++;
	}
	mlx->image = img;
}

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
	while (++n < LOOP)
	{
		if (sqrt(zx * zx + zy * zy) > DIVERGE)
			return (n);
		save_x = zx;
		zx = zx * zx - zy * zy + x;
		zy = 2 * save_x * zy + y;
	}
	return (0);
}

int	put_mandelbrot(t_mlx *mlx, t_fractal *frac)
{
	int		x;
	int		y;
	int		n;
	t_img	img;

	init_t_img(&img, mlx);
	y = 0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			n = mandelbrot_set(x, y, frac);
			if (!n)
				mlx_pixel_put_to_img(&img, x, y, 0);
			else
				mlx_pixel_put_to_img(&img, x, y, set_gradation_color(360 / LOOP * n));
			x++;
		}
		y++;
	}
	mlx->image = img;
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image.image, 0, 0);
	return (0);
}
