/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:03:08 by yliu              #+#    #+#             */
/*   Updated: 2023/10/13 11:04:55 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// if str is NULL return 0.
size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

// if dst or src is NULL, return 0.
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// free s1 before return.
char	*gnl_join_then_free(char const *s1, char const *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (dst == NULL)
	{
		free((char *)s1);
		return (NULL);
	}
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcpy(dst + s1_len, s2, s2_len + 1);
	free((char *)s1);
	return (dst);
}

// if src is NULL, return NULL.
char	*gnl_strndup(const char *src, size_t n)
{
	char	*dst;

	if (src == NULL)
		return (NULL);
	dst = malloc(sizeof(char) * (n + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, src, n + 1);
	return (dst);
}
