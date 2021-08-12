/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:03:35 by mfunyu            #+#    #+#             */
/*   Updated: 2021/08/12 20:57:46 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_spaces(const char **str)
{
	if (str)
	{
		while (**str == ' ' || **str == '\n' || **str == '\t'
			|| **str == '\v' || **str == '\f' || **str == '\r')
			(*str)++;
	}
}

double	ft_atof_check(const char *s, int *error)
{
	double	nb;
	int		sign;
	int		digits;

	nb = 0;
	digits = -1;
	sign = 1;
	*error = ERROR;
	skip_spaces(&s);
	if (*s == '-' || *s == '+')
		sign *= 44 - *s++;
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
