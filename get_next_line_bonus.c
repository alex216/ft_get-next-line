/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:53:18 by yliu              #+#    #+#             */
/*   Updated: 2023/10/28 11:56:55 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*free_then_put_null(char **pointer)
{
	free(*pointer);
	*pointer = NULL;
	return (NULL);
}

// if error, free whole_str in any case then return NULL.
// break rule of while is, either READEND or READERROR or \n
static size_t	get_whole_str_from_read(int fd, char **whole_str)
{
	char		*buf;
	ssize_t		bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (free_then_put_null(whole_str), FAILURE);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == READ_END || bytes_read == READ_ERROR)
			break ;
		buf[bytes_read] = '\0';
		*whole_str = gnl_join_then_free(whole_str, buf);
		if (whole_str == NULL)
		{
			free(buf);
			return (FAILURE);
		}
		if (gnl_strchr(buf, '\n') != NULL)
			break ;
	}
	free(buf);
	if (bytes_read == READ_ERROR)
		return (free_then_put_null(whole_str), FAILURE);
	return (SUCCESS);
}

static char	*get_one_line(char **whole_str, char *nl_pos)
{
	char		*line;

	if (nl_pos == NULL)
		line = gnl_strndup(*whole_str, gnl_strlen(*whole_str));
	else
		line = gnl_strndup(*whole_str, nl_pos - *whole_str + 1);
	return (line);
}

// first func's NULL guard is for both malloc fail and READ_ERROR.
// second and third func's NULL guard is for malloc fail.
char	*get_next_line(int fd)
{
	char		*line;
	static char	*whole_str[FD_MAX + 1];
	char		*nl_p;
	char		*rest_str;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE < 0
		|| BUFFER_SIZE > SIZE_T_MAX - 1)
		return (NULL);
	nl_p = gnl_strchr(whole_str[fd], '\n');
	if (nl_p == NULL)
	{
		if (get_whole_str_from_read(fd, &whole_str[fd]) == FAILURE)
			return (NULL);
		nl_p = gnl_strchr(whole_str[fd], '\n');
	}
	line = get_one_line(&whole_str[fd], nl_p);
	if (line == NULL || nl_p == NULL || (nl_p != NULL && *(nl_p + 1) == '\0'))
		return (free_then_put_null(&whole_str[fd]), line);
	rest_str = gnl_strndup(nl_p + 1, gnl_strlen(nl_p + 1));
	if (rest_str == NULL)
		return (free_then_put_null(&whole_str[fd]), line);
	free(whole_str[fd]);
	whole_str[fd] = rest_str;
	return (line);
}

// __attribute__ ((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }
//
////////////////////////////////////// test function
// #include <fcntl.h>
// #include <stdio.h>
// #include <errno.h>
//
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
// 	// fd1 = open("oneline_with_nl.txt", O_RDONLY);
// 	// fd1 = open("string_nl_string.txt", O_RDONLY);
// 	// fd1 = open("test.txt", O_RDONLY);
// 	// fd1 = open("multi.txt", O_RDONLY);
// 	fd1 = open("get_next_line_bonus.c", O_RDONLY);
//
// 	if (fd1 == -1)
// 	{
// 		puts("open error, not this project's fault!");
// 		return (0);
// 	}
//
// 	i = 0;
// 	while (result != NULL)
// 	{
// 		result = get_next_line(fd1);
// 		if (result == NULL)
// 			printf("[%d](null) by first errno is %d\n", i, ENOMEM);
// 		else
// 			printf("[%3d]%s", i, result);
// 		free(result);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }
