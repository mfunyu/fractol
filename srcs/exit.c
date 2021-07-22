#include "fractol.h"

void	exit_print_instruction(char *param)
{
	if (param)
		printf("fractol: invalid type -- %s\n", param);
	else
		printf("usage: ./fractol [\n");
	printf("available fractals: \n");
	printf("Julia\n");
	printf("Mandelbrot\n");
	exit(EXIT_SUCCESS);
}

int	free_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image.image);
	exit(EXIT_SUCCESS);
}
