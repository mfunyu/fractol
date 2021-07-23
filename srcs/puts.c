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
