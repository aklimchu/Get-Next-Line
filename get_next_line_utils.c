/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:02 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/13 15:44:01 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	totallen;

	totallen = ft_strlen(s1) + ft_strlen(s2);
	new_s = (char *)malloc((totallen + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	while (*s1)
	{
		*new_s = *s1;
		new_s++;
		s1++;
	}
	while (*s2)
	{
		*new_s = *s2;
		new_s++;
		s2++;
	}
	*new_s = '\0';
	return (new_s - totallen);
}

size_t	ft_strlen(const char *c)
{
	size_t		i;

	i = 0;
	while (*c)
	{
		i++;
		c++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	new_c;

	if (s == NULL)
		return((void *) 0);
	new_c = c + '\0';
	while (*s)
	{
		if (*s == new_c)
			return ((char *) s);
		s++;
	}
	if (*s == new_c)
		return ((char *) s);
	return ((void *) 0);
}

char	*write_s(char *new_s, char const *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*new_s = *s;
		s++;
		new_s++;
		i++;
	}
	*new_s = '\0';
	return (new_s - len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_s;
	unsigned int	i;

	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	if (start >= ft_strlen(s))
	{
		*new_s = '\0';
		return (new_s);
	}
	i = 0;
	while (i < start)
	{
		s++;
		i++;
	}
	new_s = write_s(new_s, s, len);
	//free((char *)s - start);	//mod
	//s = NULL;	//mod
	return (new_s);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		*(char *)s = '\0';
		s++;
		i++;
	}
	return ;
}

char	*ft_strdup(const char *s1)
{
	char	*arr;
	size_t	slen;

	slen = ft_strlen(s1);
	arr = (char *)malloc((slen + 1) * sizeof(char));
	if (arr == NULL)
	{
		errno = ENOMEM;
		return ((void *) 0);
	}
	while (*s1)
	{
		*arr = *s1;
		arr++;
		s1++;
	}
	*arr = 0;
	return (arr - slen);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (dest[i])
		i++;
	while (src[c] && c < nb)
	{
		dest[i] = src[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*add_memory(char *stash, size_t i)
{
	char	*temp;
	size_t	slen;

	slen = ft_strlen(stash);
	temp = (char *)malloc(slen + i + 1);
	while (*stash)
	{
		*temp = *stash;
		temp++;
		stash++;
	}
	*temp = '\0';
	free(stash - slen);
	return (temp - slen);
}

char	*trim_stash(char *s)
{
	char	*new_s;
	size_t	slen;
	size_t	newlen;

	slen = ft_strlen(s);
	newlen = ft_strlen(ft_strchr(s, 10)) - 1;
	if (newlen == 0)
	{
		free(s);
		return(NULL);
	}
	new_s = (char *)malloc(newlen + 1);
	while (*s != '\n' && *s)
		s++;
	s++;
	while (*s)
	{
		*new_s = *s;
		new_s++;
		s++;
	}
	*new_s = '\0';
	free(s - slen);
	return(new_s - newlen);
}
