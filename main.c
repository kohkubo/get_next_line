/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:29:19 by ncolomer          #+#    #+#             */
/*   Updated: 2021/03/17 00:01:10 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>
#include <libgen.h>
#include <stdio.h>

#include "get_next_line.h"

int main(int ac, char **av)
{
	(void)av;
	char *line = NULL;
	int i, j;

	if (ac == 1)
	{
		i = get_next_line(0, &line);
		printf("%4d : %s\n", i, line);
		free(line);
	}
	else if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		do
		{
			i = get_next_line(fd, &line);
			printf("%4d : %s\n", i, line);
			free(line);
		} while (0 < i);
	}
	else if (ac == 3)
	{
		int fd2 = open(av[1], O_RDONLY);
		int fd3 = open(av[2], O_RDONLY);
		printf("fd1 : %d\nfd2 : %d\n", fd2, fd3);
		do
		{
			i = get_next_line(fd2, &line);
			printf("%4d : %s\n", i, line);
			free(line);

			j = get_next_line(fd3, &line);
			printf("%4d : %s\n", j, line);
			free(line);
		} while (0 < i || 0 < j);
	}
	return (0);
}
