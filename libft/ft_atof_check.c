/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:03:35 by mfunyu            #+#    #+#             */
/*   Updated: 2021/08/13 13:57:08 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_sign(const char **str)
{
	int		sign;

	sign = 1;
	while (**str == ' ' || **str == '\n' || **str == '\t'
		|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		sign *= 44 - **str;
		(*str)++;
	}
	return (sign);
}

double	ft_atof_check(const char *s, int *error)
{
	double	nb;
	int		sign;
	int		digits;

	*error = ERROR;
	if (!s)
		return (0);
	nb = 0;
	digits = -1;
	sign = set_sign(&s);
	while (ft_isdigit(*s) || (*s == '.' && digits == -1))
	{
		*error = 1;
		if (*s == '.' || digits >= 0)
			digits++;
		if (digits != 0)
			nb = nb * 10 + (*s - '0');
		s++;
	}
	if (*error == 1 && *s == '\0')
		*error = SUCCESS;
	while (digits-- > 0)
		nb /= 10;
	return (nb * sign);
}
