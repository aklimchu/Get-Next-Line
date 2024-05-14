/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:21:22 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/13 15:53:47 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	static char	*stash = NULL;
	int			bytes_read;

	if (BUFFER_SIZE < 0 || BUFFER_SIZE / (SIZE_MAX - 1) > 1 || fd < 0 || read(fd, 0, 0))
	{
		//free(stash);
		//stash = NULL;
		return ((void *) 0);
	}
	line = NULL;
	bytes_read = 1;
	if (stash == NULL)
		stash = ft_strdup("");
	while (ft_strchr(stash, 10) == NULL && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			// freeing memory?
			return ((void *) 0);
		}
		/*if (bytes_read == 0)
		{
			break ; 
		}*/
		// check the case of empty line / no more lines in the file
		*(buffer + bytes_read) = '\0';
		stash = add_memory(stash, bytes_read); //protect malloc?
		stash = ft_strncat(stash, buffer, ft_strlen(stash) + ft_strlen(buffer) + 1); //bezero buffer?
	}
	if (ft_strchr(stash, 10) == NULL)
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
	}
	else if (ft_strchr(stash, 10))
	{
		line = ft_substr(stash, 0, ft_strlen(stash) - ft_strlen(ft_strchr(stash, 10)) + 1);
		stash = trim_stash(stash);
	}
	return(line);
}
