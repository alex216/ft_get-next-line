/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:03:31 by yliu              #+#    #+#             */
/*   Updated: 2023/10/13 18:08:01 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>


enum e_read_return_value {
    READ_ERROR  = -1,
    READ_END    = 0
};

// int			main(void);
char		*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *str);
char		*gnl_join_then_free(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *src);

#endif
