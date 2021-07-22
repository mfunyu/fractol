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

bool	is_in_mandelbrot_set(double x, double y)
{
	double	zx;
	double	zy;
	double	save_x;
	int		i;

	x = x / (WIDTH / (X_MAX - X_MIN)) + X_MIN;
	y = y / (HEIGHT / (Y_MAX - Y_MIN)) + Y_MIN;
	zx = 0;
	zy = 0;
	i = -1;
	while (++i < LOOP)
	{
		if (sqrt(zx * zx + zy * zy) > DIVERGE)
			return (false);
		save_x = zx;
		zx = zx * zx - zy * zy + x;
		zy = 2 * save_x * zy + y;
	}
	return (true);
}

void	put_mandelbrot(t_mlx *mlx)
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
			if (is_in_mandelbrot_set(x, y))
				mlx_pixel_put_to_img(&img, x, y, 255);
			else
				mlx_pixel_put_to_img(&img, x, y, 0);
			x++;
		}
		y++;
	}
	mlx->image = img;
}
