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

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash = NULL; // will this pass norminette?
	int			res;

	line = NULL;
	res = 1;	
	//operating with stash
	printf("Stash in the beginning: %s", stash);  //delete
	if (stash && ft_strchr(stash, 10))
	{
		line = ft_substr(stash, 0, ft_strlen(stash) - ft_strlen(ft_strchr(stash, 10)) + 1);
		if (ft_strlen(ft_strchr(stash, 10)) > 1) 
			stash = ft_strchr(stash, 10) + 1;
		else
			free(stash);
		return (line);
	}
	if (stash && ft_strchr(stash, 10) == NULL)
	{
		line = ft_strjoin(line, stash);
		free(stash);
		stash = NULL;
	}
	printf("Line after merging with stash: %s", line); //delete
	//operating with buffer
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return ((void *) 0);
	while (buffer && ft_strchr(line, 10) == NULL /*&& res != 0*/) // does it work with end of file?
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1)
			return ((void *) 0);
		if (res == 0)
			break ;
		*(buffer + BUFFER_SIZE) = '\0';
		if (buffer && ft_strchr(buffer, 10) == NULL)
			line = ft_strjoin(line, buffer);
		if (buffer && ft_strchr(buffer, 10))
		{
			line = ft_strjoin(line, ft_substr(buffer, 0, \
				ft_strlen(buffer) - ft_strlen(ft_strchr(buffer, 10)) + 1)); //protecting substr?
			if (ft_strlen(ft_strchr(buffer, 10)) > 1) 
				stash = ft_strjoin(stash, ft_strchr(buffer, 10) + 1); // what if end of file?
			printf("Stash in the end: %s", stash);
		}
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
	free(buffer);
	return (line);
}
