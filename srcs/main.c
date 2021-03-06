/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 21:20:06 by mfunyu            #+#    #+#             */
/*   Updated: 2021/08/12 21:07:29 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_t_mlx(t_mlx *mlx, char **av)
{
	mlx->mlx = mlx_init();
	mlx->screen = set_screen_size(mlx, NULL);
	mlx->window = mlx_new_window(mlx->mlx, mlx->screen, mlx->screen, av[1]);
	if (!mlx->window)
		error_exit("mlx window");
}

void	init_t_fractal(t_fractal *fractal, t_mlx *mlx)
{
	fractal->screen = mlx->screen;
	fractal->type = set_fractal_type(NULL);
	fractal->x_min = MIN;
	fractal->y_min = MIN;
	fractal->size = SIZE;
	fractal->c_real = set_fractal_vals(NULL, true);
	fractal->c_imag = set_fractal_vals(NULL, false);
	fractal->color = 0;
	fractal->resolution = set_resolution(NULL);
	fractal->loop = calc_loop(fractal);
	fractal->change = 0;
	mlx->fractal = fractal;
}

void	start_mlx_loop(t_mlx *mlx)
{
	mlx_key_hook(mlx->window, key_hook, mlx);
	mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_hook(mlx->window, MotionNotify, PointerMotionMask, mouse_motion, mlx);
	mlx_hook(mlx->window, DestroyNotify, StructureNotifyMask, just_exit, NULL);
	mlx_hook(mlx->window, FocusIn, FocusChangeMask, put_fractal, mlx);
	mlx_hook(mlx->window, KeyPress, KeyPressMask, key_press, mlx);
	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_fractal	frac;

	check_params(ac, av);
	init_t_mlx(&mlx, av);
	init_t_fractal(&frac, &mlx);
	put_fractal(&mlx);
	start_mlx_loop(&mlx);
	return (0);
}
