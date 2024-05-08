/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:02 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/08 15:25:00 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

size_t	checknew(char c, char const *set)
{
	size_t	count;
	
	count = 0;
	while (*set && *set != c)
	{
		count++;
		set++;
	}
	if (*set == c)
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	lensrc;
	size_t	i;

	lensrc = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (lensrc);
	while (i + 1 < dstsize && (*src))
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = 0;
	return (lensrc);
}

char	*ft_strchr(const char *s, int c)
{
	char	new_c;

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
	return (new_s);
}
