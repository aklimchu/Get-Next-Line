/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:28:53 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/08 15:27:36 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int argc, char *argv[])
{
	int		fd;
	int		i;

	if (argc < 2)
	{
		printf("Not enough arguments");
		return (1);
	}
	if (argc > 2)
	{
		printf("Too many arguments");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error while file opening");
		return (1);
	}
	i = 0;
	while (i < 5)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	return (0);
}
