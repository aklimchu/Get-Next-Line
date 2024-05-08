/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:19:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/08 13:10:33 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;	
	char		*line;
	int			res;
	static int	fd_count;
	size_t		checknl;
	
	fd_count = fd;
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (buffer == NULL)
		return ((void *) 0);
	res = read(fd_count, buffer, BUFFER_SIZE);
	if (res == -1 || res == 0)
		return ((void *) 0);
	checknl = checknew('\n', buffer); 
	line = (char *)malloc((checknl + 1) * sizeof(char));
	if (line == NULL)
		return ((void *) 0);
	ft_strlcpy(line, buffer, checknl + 1);
	//buffer = buffer + checknew('\n', buffer);
	fd_count = fd_count + checknl;
	free(buffer);
	return (line);
}
