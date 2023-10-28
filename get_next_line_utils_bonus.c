/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:54:52 by yliu              #+#    #+#             */
/*   Updated: 2023/10/28 10:55:03 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// if str is NULL return 0.
size_t	gnl_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

// original libft
char	*gnl_strchr(const char *s, int c)
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
size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	src_len = gnl_strlen(src);
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

// if src is NULL, return NULL.
char	*gnl_strndup(const char *src, size_t n)
{
	char	*dst;

	if (src == NULL)
		return (NULL);
	dst = malloc(sizeof(char) * (n + 1));
	if (dst == NULL)
		return (NULL);
	gnl_strlcpy(dst, src, n + 1);
	return (dst);
}

// free s1 before return.
// s1 is a pointer must allocating somewhere.
// s2:NULL is impossible due to READ_ERROR is
// considered. however, it returns s1.
char	*gnl_join_then_free(char **s1, char const *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = gnl_strlen(*s1);
	s2_len = gnl_strlen(s2);
	if (s1 == NULL || (*s1 == NULL && s2 == NULL))
		return (NULL);
	if (*s1 == NULL)
	{
		dst = gnl_strndup(s2, gnl_strlen(s2));
		return (dst);
	}
	if (s2 == NULL)
		return (*s1);
	dst = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (dst == NULL)
	{
		free(*s1);
		return (NULL);
	}
	gnl_strlcpy(dst, *s1, s1_len + 1);
	gnl_strlcpy(dst + s1_len, s2, s2_len + 1);
	free(*s1);
	return (dst);
}
