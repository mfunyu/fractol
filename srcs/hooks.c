#include "fractol.h"

int	key_hook(int key, t_mlx *mlx)
{
	DI(key);
	if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		free_exit(mlx);
	}
	return (0);
}
