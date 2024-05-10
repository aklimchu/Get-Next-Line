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
#include <stdio.h> // delete
#include <stdint.h> // do we need this? (SIZE_MAX)

// how can we set default BUFFER_SIZE?

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash = NULL; // will this pass norminette?
	int			res;

	if (BUFFER_SIZE / (SIZE_MAX - 1) > 1)
		return ((void *) 0);
	line = NULL;
	res = 1;	
	//operating with stash
	//printf("Stash in the beginning: %s\n", stash);  //delete
	if (stash && ft_strchr(stash, 10))
	{
		line = ft_substr(stash, 0, ft_strlen(stash) - ft_strlen(ft_strchr(stash, 10)) + 1);
		if (ft_strlen(ft_strchr(stash, 10)) > 1) 
			stash = ft_substr(stash, ft_strlen(stash) - ft_strlen(ft_strchr(stash, 10) + 1), \
				ft_strlen(ft_strchr(stash, 10)) - 1);
		else
		{	
			free(stash);
			stash = NULL;
		}
		return (line);
	}
	if (stash && ft_strchr(stash, 10) == NULL)
	{
		line = ft_strjoin(line, stash);
		//ft_bzero(stash, ft_strlen(stash));
		free(stash);
		stash = NULL;
	}
	//printf("Line after merging with stash: %s\n", line); //delete
	//operating with buffer
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return ((void *) 0);
	while (buffer && ft_strchr(line, 10) == NULL /*&& res != 0*/) // does it work with end of file?
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1)
		{	
			free(buffer);
			if (line)
				free(line);
			if (stash)
				free(stash);
			return ((void *) 0);
		}
		if (res == 0)
			break ;
		*(buffer + res) = '\0';
		if (buffer && ft_strchr(buffer, 10) == NULL /*&& res*/)
			line = ft_strjoin(line, buffer);
		if (buffer && ft_strchr(buffer, 10))
		{
			line = ft_strjoin(line, ft_substr(buffer, 0, \
				ft_strlen(buffer) - ft_strlen(ft_strchr(buffer, 10)) + 1)); //protecting substr?
			if (ft_strlen(ft_strchr(buffer, 10)) > 1) 
				stash = ft_strjoin(stash, ft_strchr(buffer, 10) + 1); // what if end of file?
		}
		ft_bzero(buffer, res);
	}
	//printf("Stash in the end: %s\n", stash);
	free(buffer);
	return (line);
}
