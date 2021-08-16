/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 21:19:57 by mfunyu            #+#    #+#             */
/*   Updated: 2021/08/16 22:54:51 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	ignore(t_fractal *fractal)
{
	static int	ignore;

	if (ignore++ >= INT_MAX - 1)
		ignore = 0;
	if (fractal->loop > 100 && ignore % (fractal->loop / IGNORE_FREQ))
		return (true);
	return (false);
}

int	key_hook(int key, t_mlx *mlx)
{
	t_fractal	*fr;

	fr = mlx->fractal;
	if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit(EXIT_SUCCESS);
	}
	if (key == INFO)
	{
		printf("x: [%f, %f], y: [%f, %f], loop: %d, color: %s\n",
			fr->x_min, fr->x_min + fr->size, fr->y_min, fr->y_min + fr->size,
			fr->loop, t_color_to_char(fr->color));
		return (0);
	}
	if (key == COLOR)
	{
		if (++fr->color == Num_colors)
			fr->color = 0;
	}
	else if (key == RESET)
		init_t_fractal(fr, mlx);
	put_fractal(mlx);
	return (0);
}

int	key_press(int key, t_mlx *mlx)
{
	t_fractal	*fr;

	fr = mlx->fractal;
	if (ignore(mlx->fractal))
		return (0);
	if (key == INC || key == DEC)
	{
		if (key == INC)
		{
			fr->loop += 4;
			ft_putendl_fd("increasing loops ...", STDOUT_FILENO);
		}
		else
		{
			if (fr->loop == LOOP_MIN)
				return (0);
			fr->loop = max(LOOP_MIN, fr->loop - 4);
			ft_putendl_fd("decreasing loops ...", STDOUT_FILENO);
		}
		put_fractal(mlx);
		ft_putendl_fd(CLEAR_SCREEN, STDOUT_FILENO);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	if (ignore(mlx->fractal))
		return (0);
	if (button == UP || button == DOWN)
	{
		if (button == UP)
		{
			set_zoom(mlx->fractal, x, y, 1);
			ft_putendl_fd("zooming in ...", STDOUT_FILENO);
			mlx->fractal->loop = max(mlx->fractal->loop,
					calc_loop(mlx->fractal));
		}
		if (button == DOWN)
		{
			set_zoom(mlx->fractal, x, y, -1);
			ft_putendl_fd("zooming out ...", STDOUT_FILENO);
			mlx->fractal->loop = min(mlx->fractal->loop,
					calc_loop(mlx->fractal));
		}
	}
	put_fractal(mlx);
	ft_putendl_fd(CLEAR_SCREEN, STDOUT_FILENO);
	return (0);
}

int	mouse_motion(int x, int y, t_mlx *mlx)
{
	static int	cnt;

	(void)x;
	(void)y;
	if (mlx->fractal->color == Rainbow)
	{
		if (cnt++ >= INT_MAX - 1)
			cnt = 0;
		if (cnt % CHANGE_FREQ)
			return (0);
		mlx->fractal->change++;
		if (mlx->fractal->change >= mlx->fractal->loop)
			mlx->fractal->change = 0;
		put_fractal(mlx);
	}
	return (0);
}
