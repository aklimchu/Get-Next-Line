/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:19:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/08 11:47:32 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*temp;
	char			*line;
	//static int		BUFFER_SIZE;
	static int		fd_count;
	long int		size;
	int				res;
	
	fd_count = fd;
	temp = (char *)malloc(1);
	line = (char *)malloc(2);
	//BUFFER_SIZE = 1024;
	if (BUFFER_SIZE == 0)
		return (NULL);
	res = 0;
	res = read(fd_count, line, 1);
	*(line + 1) = '\0';
 	size = 1;
	while (res == 1 && *temp != '\n' && *line != '\n'  && size < BUFFER_SIZE)
	{
		res = read(fd, temp, 1);
		line = ft_strjoin(line, temp);
		size++;
	}
	if (res == -1)
		return (NULL);
	fd_count = fd_count + res;
	return (line);
}
