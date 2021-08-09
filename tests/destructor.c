/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 21:20:06 by mfunyu            #+#    #+#             */
/*   Updated: 2021/08/09 21:39:38 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void	leak_checker(void)__attribute__((destructor));

void	leak_checker(void)
{
	int		status;

	status = system("leaks fractol > ./tests/log");
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		system("grep -C2 malloced ./tests/log");
		fprintf(stderr, "%sOK! No memory leaks :)%s\n", GREEN, RESET);
	}
	else
	{
		system("grep TOTAL -A10 ./tests/log");
		fprintf(stderr, "%sKO! Memory leak detected :(%s\n", RED, RESET);
	}
}
