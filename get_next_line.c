/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:58:34 by yliu              #+#    #+#             */
/*   Updated: 2023/10/13 18:07:48 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

static char	*get_whole_str_from_read(int fd, char *whole_str)
{
	char		*buf;
	int			bytes_read;
	char		*return_addr;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == READ_ERROR | bytes_read == READ_END)
			break;
		buf[bytes_read] = '\0';
		if (buf == NULL)
			break ;
		whole_str = ft_strjoin(whole_str, buf);
		return_addr = ft_strchr(buf, '\n');
		if (return_addr)
		{
			break;
		}
	}
	free(buf);
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
		return (ft_strdup(""));
	line_size = ft_strchr(whole_str, '\0') - nl_index;
	dst = malloc(sizeof(char) * line_size);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, nl_index + 1, line_size);
	return (dst);
}

#include <string.h>
char	*get_next_line(int fd)
{
	static char	*whole_str = "";
	char		*line;

	// 1.
	whole_str = get_whole_str_from_read(fd, whole_str);
	if (whole_str == NULL)
		return (NULL);

	// 2.
	line = get_one_line(whole_str);
	if (line == NULL)
		return (NULL);

//	printf("line: %s\n", line);
//	printf("len %lu\n", strlen(line));
//	for (size_t i = 0;i < strlen(line); i++)
//		printf("%d |", line[i]);

	// 3.
	whole_str = get_next_whole_str(whole_str);
	printf("%s\n", whole_str);
	if (whole_str == NULL)
		return (NULL);

//	printf("whole2: %s\n", whole_str);
	printf("wholestr: '%s' len is %lu :", whole_str, strlen(whole_str));
	for (size_t i = 0;i < strlen(whole_str); i++)
		printf("%d |", whole_str[i]);

	return (line);
}

////////////////////////////////////////// test function
int	main(void)
{
	int fd1;
	char *result;

//	fd1 = open("empty.txt", O_RDONLY);
//	fd1 = open("emptyreal.txt", O_RDONLY);
	fd1 = open("test.txt", O_RDONLY);
//	fd1 = 0;
//	fd1 = open("oneline_with_nl.txt", O_RDONLY);
//	fd1 = open("oneline_withno_nl.txt", O_RDONLY);
	if (fd1 == -1)
	{
		puts("open error, not this project's fault!");
		return (0);
	}

	result = get_next_line(fd1);
	if (result == NULL)
	{
		puts("null return from gnl.c by gnl");
		printf("errno is %d\n", errno);
		return (0);
	}
	puts("\n#### first line ####");
	printf("%s", result);
	puts("#### first line ####\n");

	result = get_next_line(fd1);
	if (result == NULL)
	{
		puts("null return from gnl.c");
		printf("errno is %d\n", errno);
		return (0);
	}
	puts("\n#### second line ####");
	printf("%s", result);
	puts("#### second line ####\n");

	result = get_next_line(fd1);
	if (result == NULL)
	{
		puts("null return from gnl.c");
		printf("errno is %d\n", errno);
		return (0);
	}
	puts("\n#### third line ####");
	printf("%s", result);
	puts("#### third line ####\n");

	free(result);
	close(fd1);
	return (0);
}
