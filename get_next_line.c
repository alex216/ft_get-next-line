/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:58:34 by yliu              #+#    #+#             */
/*   Updated: 2023/10/23 23:29:46 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <string.h>
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif

static char	*get_whole_str_from_read(int fd, char *whole_str)
{
	char	*buf;
	int		bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
	{
		free(whole_str);
		return (NULL);
	}
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == READ_ERROR | bytes_read == READ_END)
			break ;
		buf[bytes_read] = '\0';
		whole_str = gnl_join_then_free(whole_str, buf);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	free(buf);
	if (bytes_read == READ_ERROR
		|| (bytes_read == READ_END && *whole_str == '\0'))
	{
		free(whole_str);
		return (NULL);
	}
	return (whole_str);
}

static char	*get_one_line(char *whole_str)
{
	char	*line;
	size_t	line_size;
	char	*nl_index;

	nl_index = ft_strchr(whole_str, '\n');
	if (nl_index == NULL)
		return (ft_strdup(whole_str));
	line_size = nl_index - whole_str;
	line = malloc(sizeof(char) * line_size + 2);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, whole_str, line_size + 2);
	return (line);
}

static char	*get_next_whole_str(char *whole_str)
{
	char	*rest_str;
	size_t	line_size;
	char	*nl_index;

	nl_index = ft_strchr(whole_str, '\n');
	if (nl_index == NULL)
	{
		free(whole_str);
		return (NULL);
	}
	line_size = ft_strchr(whole_str, '\0') - nl_index;
	rest_str = malloc(sizeof(char) * line_size);
	if (rest_str == NULL)
	{
		free(whole_str);
		return (NULL);
	}
	ft_strlcpy(rest_str, nl_index + 1, line_size);
	free(whole_str);
	return (rest_str);
}

// first func's NULL guard is for both malloc fail and READ_ERROR.
// second func's NULL guard is for malloc fail.
// third funct does need NULL return.
char	*get_next_line(int fd)
{
	char		*line;
	static char	*whole_str;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE < 0 || BUFFER_SIZE > SIZE_T_MAX - 1)
		return (NULL);
	if (whole_str == NULL)
		whole_str = ft_strdup("");
	whole_str = get_whole_str_from_read(fd, whole_str);
	if (whole_str == NULL)
		return (NULL);
	line = get_one_line(whole_str);
	if (line == NULL)
		return (NULL);
	whole_str = get_next_whole_str(whole_str);
	return (line);
}

//
// //////////////////////////////////////// test function
// int	main(void)
// {
// 	int		fd1;
// 	int		i;
// 	char	*result;
//
// 	// fd1 = 0;
// 	// fd1 = open("empty.txt", O_RDONLY);
// 	// fd1 = open("nl.txt", O_RDONLY);
// 	// fd1 = open("oneline_withno_nl.txt", O_RDONLY);
// 	fd1 = open("oneline_with_nl.txt", O_RDONLY);
// 	// fd1 = open("string_nl_string.txt", O_RDONLY);
// 	// fd1 = open("test.txt", O_RDONLY);
// 	// fd1 = open("multi.txt", O_RDONLY);
//
// 	if (fd1 == -1)
// 	{
// 		puts("open error, not this project's fault!");
// 		return (0);
// 	}
//
// 	i = 0;
// 	while (i < 12 && result != NULL)
// 	{
// 		result = get_next_line(fd1);
// 		if (result == NULL)
// 			printf("###%d is###:(null) by first errno is %d\n", i, ENOMEM);
// 		else
// 			printf("###%d is###:%s\n", i, result);
// 		free(result);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }
