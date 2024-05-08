/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:19:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/08 15:50:49 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;
	int			res;

	stash = NULL;
	line = NULL;
	res = 1;	
	//operating with stash
	if (stash && ft_strchr(stash, 10))
	{
		line = ft_substr(stash, 0, ft_strlen(stash) - ft_strlen(ft_strchr(stash, 10)));
		stash = ft_strchr(stash, 10) + 1;
		return (line);
	}
	if (stash && ft_strchr(stash, 10) == NULL)
	{
		line = ft_strjoin(line, stash);
		free(stash);
	}
	//operating with buffer
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (buffer == NULL)
		return ((void *) 0);
	//while (buffer && /*ft_strchr(line, 10) == NULL &&*/ res != 0)
	//{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1)
			return ((void *) 0);
		if (buffer && ft_strchr(buffer, 10) == NULL)
			line = ft_strjoin(line, buffer); //segfaults here
		if (buffer && ft_strchr(buffer, 10))
		{
			line = ft_substr(buffer, 0, ft_strlen(buffer) - ft_strlen(ft_strchr(buffer, 10)) + 1);
			stash = ft_strjoin(stash, ft_strchr(buffer, 10) + 1);
		}
		//buffer = NULL;
//	}
	free(buffer);
	return (line);
}
