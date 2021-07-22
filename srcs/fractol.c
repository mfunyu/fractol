#include "fractol.h"

bool	is_valid_parameter(char *param)
{
	if (ft_strncmp("Julia", param, 6))
		return (true);
	if (ft_strncmp("Mandelbrot", param, 11))
		return (true);
	return (false);
}

void	init_t_mlx(t_mlx *mlx, char *name)
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, name);
}

void	start_mlx_loop(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image.image, 0, 0);
	mlx_key_hook(mlx->window, &key_hook, mlx);
	mlx_hook(mlx->window, DESTROY_NOTIFY,
		STRUCTURE_NOTIFY_MASK, &free_exit, (void *)mlx);
	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac <= 1 || !is_valid_parameter(av[1]))
		exit_print_instruction(av[1]);
	init_t_mlx(&mlx, av[1]);
	put_mandelbrot(&mlx);
	start_mlx_loop(&mlx);
	return (0);
}
