/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:55:52 by yliu              #+#    #+#             */
/*   Updated: 2023/10/28 10:57:00 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

enum	e_read_return_value
{
	READ_ERROR = -1,
	READ_END = 0
};

char	*get_next_line(int fd);

size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
char	*gnl_strndup(const char *src, size_t n);
char	*gnl_join_then_free(char **s1, char const *s2);

#endif
