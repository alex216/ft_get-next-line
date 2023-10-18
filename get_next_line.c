/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:58:34 by yliu              #+#    #+#             */
/*   Updated: 2023/10/17 17:42:07 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

static char	*get_whole_str_from_read(int fd, char *whole_str)
{
	char	*buf;
	int		bytes_read;
	char	*tmp_str;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == READ_ERROR)
			break ;
		if (bytes_read == READ_END)
			break ;
		buf[bytes_read] = '\0';
		tmp_str = ft_strjoin(whole_str, buf);
		free(whole_str);
		whole_str = tmp_str;
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	free(buf);
	if (bytes_read == READ_ERROR)
		return (NULL);
	if (bytes_read == READ_END)
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
		return (whole_str);
	line_size = nl_index - whole_str;
	line = malloc(sizeof(char) * line_size + 2);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, whole_str, line_size + 2);
	return (line);
}

static char	*get_next_whole_str(char *whole_str)
{
	char	*dst;
	size_t	line_size;
	char	*nl_index;

	nl_index = ft_strchr(whole_str, '\n');
	if (nl_index == NULL)
	{
		free(whole_str);
		return (ft_strdup(""));
	}
	line_size = ft_strchr(whole_str, '\0') - nl_index;
	dst = malloc(sizeof(char) * line_size);
	if (dst == NULL)
	{
		free(whole_str);
		return (NULL);
	}
	ft_strlcpy(dst, nl_index + 1, line_size);
	free(whole_str);
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*whole_str;// = "";
	char		*line;

	//	whole_str = "";
	// 1.
	whole_str = get_whole_str_from_read(fd, whole_str);
	if (whole_str == NULL)
		return (NULL);

	// 2.
	line = get_one_line(whole_str);
	if (line == NULL)
		return (NULL);

	// 3.
	whole_str = get_next_whole_str(whole_str);
	if (whole_str == NULL)
		return (NULL);

	return (line);
}

//////////////////////////////////////// test function
int	main(void)
{
	int		fd1;
	char	*result;

	//fd1 = open("empty.txt", O_RDONLY);
	fd1 = open("nl.txt", O_RDONLY);
	//fd1 = open("test.txt", O_RDONLY);
	//fd1 = 0;
	//fd1 = open("oneline_with_nl.txt", O_RDONLY);
	//fd1 = open("oneline_withno_nl.txt", O_RDONLY);
	//fd1 = open("string_nl_string.txt", O_RDONLY);
	if (fd1 == -1)
	{
		puts("open error, not this project's fault!");
		return (0);
	}

	result = get_next_line(fd1);
	puts("\n#### first line ####");
	if (result == NULL)
		printf("(null) by first errno is %d\n", ENOMEM);
	else
		printf("%s", result);
	puts("#### first line ####\n");

	result = get_next_line(fd1);
	puts("\n#### second line ####");
	if (result == NULL)
		printf("(null) by second errno is %d\n", ENOMEM);
	else
		printf("%s", result);
	puts("#### second line ####\n");

	result = get_next_line(fd1);
	puts("\n#### third line ####");
	if (result == NULL)
		printf("(null) by third errno is %d\n", ENOMEM);
	else
		printf("%s", result);
	puts("#### third line ####\n");

	free(result);
	close(fd1);
	return (0);
}

