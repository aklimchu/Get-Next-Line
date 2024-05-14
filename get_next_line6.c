/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:19:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/13 12:21:44 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // delete

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	static char	*stash = NULL;
	int			res;

	if (BUFFER_SIZE < 0 || BUFFER_SIZE / (SIZE_MAX - 1) > 1 || fd < 0 || read(fd, 0, 0))
	{
		free(stash);
		stash = NULL;
		return ((void *) 0);
	}
	res = 1;
	line = ft_strdup("");
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
		free(stash);
		stash = NULL;
	}
	//printf("Line after merging with stash: %s\n", line); //delete
	//operating with buffer
	while (ft_strchr(line, 10) == NULL /*&& res != 0*/) // does it work with end of file?
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1)
		{	
			if (line)
				free(line);
			if (stash)
				free(stash);
			return ((void *) 0);
		}
		if (res == 0)
		{
			if (stash)
				free(stash);
			/*free (line);
			line = NULL;*/
			break ;
		}
		*(buffer + res) = '\0';
		if (ft_strchr(buffer, 10) == NULL /*&& res*/)
			line = ft_strjoin(line, buffer);
		else if (ft_strchr(buffer, 10))  // else if?
		{
			line = ft_strjoin(line, ft_substr(buffer, 0, \
				ft_strlen(buffer) - ft_strlen(ft_strchr(buffer, 10)) + 1));
			if (ft_strlen(ft_strchr(buffer, 10)) > 1) 
			{
				stash = ft_strdup("");
				stash = ft_strjoin(stash, ft_strchr(buffer, 10) + 1); // what if end of file?
			}
		}
		ft_bzero(buffer, res);
	}
	//printf("Stash in the end: %s\n", stash);
	return (line); // check for NULL in strjoin and substr
	// is stash properly freed if end of file?
}
