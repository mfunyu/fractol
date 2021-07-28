#include "fractol.h"

void	mlx_pixel_put_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + x * (img->bpp / 8) + (y * img->line_len);
	*(unsigned int *)dst = color;
}

void	init_t_img(t_img *img, t_mlx *mlx)
{
	img->image = mlx_new_image(mlx->mlx, mlx->screen, mlx->screen);
	img->addr = mlx_get_data_addr(img->image, &img->bpp, &img->line_len,
			&img->endian);
}

int	is_in_set(double x, double y, t_fractal *fractal)
{
	if (fractal->type == Julia)
		return (julia_set(x, y, fractal));
	if (fractal->type == Mandelbrot)
		return (mandelbrot_set(x, y, fractal));
	return (0);
}

int	put_fractal(t_mlx *mlx)
{
	int		x;
	int		y;
	int		n;
	t_img	img;

	init_t_img(&img, mlx);
	y = 0;
	while (y < mlx->screen)
	{
		x = 0;
		while (x < mlx->screen)
		{
			n = is_in_set(x, y, mlx->fractal);
			if (!n)
				mlx_pixel_put_to_img(&img, x, y, 0);
			else
				mlx_pixel_put_to_img(&img, x, y,
					set_gradation_color(360.0 / mlx->fractal->loop * n));
			x++;
		}
		y++;
	}
	mlx->image = img;
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image.image, 0, 0);
	return (0);
}
