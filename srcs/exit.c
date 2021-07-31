#include "fractol.h"

void	exit_print_instruction(char *param, char *option)
{
	if (param)
		printf("fractol: invalid type --  %s\n", param);
	if (option)
		printf("fractol: illegal option: %s\n", option);
	printf(INSTRUCTIONS);
	exit(EXIT_SUCCESS);
}

int	free_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image.image);
	exit(EXIT_SUCCESS);
}

int	error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	null_free(void **val)
{
	free(*val);
	*val = NULL;
}
