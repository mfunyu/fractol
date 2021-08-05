/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 21:20:28 by mfunyu            #+#    #+#             */
/*   Updated: 2021/08/05 21:20:28 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
