/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 21:20:02 by mfunyu            #+#    #+#             */
/*   Updated: 2021/08/11 21:42:41 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** x / frac->screen :
** calc percentage of the pixel length (px_0 to px_x)
** in relation to the total screen pixel size
** * frac->size :
** convert the pixel length to a size of the fractal's complex plane
** frac->x_min + :
** add a value of the px_0 coordinate to the px_x length
*/

int	julia_set(double x, double y, t_fractal *frac)
{
	double	zx;
	double	zy;
	double	save_x;
	int		n;

	zx = frac->x_min + x / frac->screen * frac->size;
	zy = frac->y_min + (1 - y / frac->screen) * frac->size;
	n = 1;
	while (n <= frac->loop)
	{
		if (zx * zx + zy * zy < -DIVERGE || zx * zx + zy * zy > DIVERGE)
			return (n);
		save_x = zx;
		zx = zx * zx - zy * zy + frac->c_real;
		zy = 2 * save_x * zy + frac->c_imag;
		n++;
	}
	return (0);
}
