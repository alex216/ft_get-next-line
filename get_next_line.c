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

#define BUFFER_SIZE 5

static char	*get_whole_str_from_read(int fd, char *whole_str)
{
	char		*buf;
	int			bytes_read;
	char		*return_addr;
	size_t		line_size;

	line_size = ft_strchr(whole_str, '\0') - whole_str;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == READ_ERROR | bytes_read == READ_END)
			break;
		printf("buf: %s\n", buf);
		if (buf == NULL)
			break ;
		whole_str = ft_strjoin(whole_str, buf);
		return_addr = ft_strchr(buf, '\n');
		if (return_addr)
		{
			line_size += return_addr - buf;
			printf("line_size: %ld\n", line_size);
			break;
		}
		line_size += BUFFER_SIZE;
	}
	free(buf);
	return (whole_str);
}

//static char	*get_one_line(char *whole_str)
//{
//	char	*line;
//	size_t	line_size;
//
//	line_size = ft_strchr(whole_str, '\n') - whole_str;
//	line = malloc(sizeof(char) * line_size + 1);
//	if (line == NULL)
//		return (NULL);
//	ft_strlcpy(line, whole_str, line_size + 1);
//	return (line);
//}

//static char	*get_next_whole_str(char *whole_str)
//{
//	char	*dst;
//	size_t	line_size;
//
//	line_size = ft_strchr(whole_str, '\n') - whole_str;
//	dst = malloc(sizeof(char) * line_size + 1);
//	if (dst == NULL)
//		return (NULL);
//	ft_strlcpy(dst, whole_str + line_size , BUFFER_SIZE);
//	return (dst);
//}

char	*get_next_line(int fd)
{
	static char	*whole_str = "";
	//char		*line;

	// 1.
	whole_str = get_whole_str_from_read(fd, whole_str);
	if (whole_str == NULL)
		return (NULL);
	printf("whole: %s\n", whole_str);

//	// 2.
//	line = get_one_line(whole_str);
//	if (line == NULL)
//		return (NULL);
//	printf("line: %s\n", line);

//	// 3.
//	whole_str = get_next_whole_str(whole_str);
//	if (whole_str == NULL)
//		return (NULL);
//	printf("whole2: %s\n", whole_str);

	return (NULL);
//	return (line);
}

////////////////////////////////////////// test function
int	main(void)
{
	int fd1;
	char *result;

	// fd1 = open("empty.txt", O_RDONLY);
	fd1 = open("test.txt", O_RDONLY);
	if (fd1 == -1)
		return (0);
	result = get_next_line(fd1);
	if (result == NULL)
		return (0);
	puts("\n#### first line ####");
	printf("%s\n", result);
	puts("#### first line ####\n");

//	result = get_next_line(fd1);
//	puts("\n#### second line ####");
//	printf("%s\n", result);
//	puts("#### second line ####\n");

	free(result);
	close(fd1);
	return (0);
}
