/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:58:34 by yliu              #+#    #+#             */
/*   Updated: 2023/10/13 13:03:59 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

#define BUFFER_SIZE 5

static char	*get_whole_str_from_read(int fd, char *whole_str, size_t *line_size)
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
			break ;
		whole_str = ft_strjoin(whole_str, buf);
		return_addr = ft_strchr(buf, '\n');
		if (return_addr)
		{
			//whole_str[*line_size + (return_addr - buf)] = '\0';
			whole_str[*line_size + BUFFER_SIZE] = '\0';
			*line_size += return_addr - buf;
			break ;
		}
		*line_size += BUFFER_SIZE;
	}
	free(buf);
	return (whole_str);
}

static char	*get_one_line(char *whole_str, size_t *line_size)
{
	char	*line;

	line = malloc(sizeof(char) * *line_size + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, whole_str, *line_size + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*whole_str;
	char		*line;
	size_t		*line_size = NULL;


	size_t	a = 0;
	line_size = &a;
	whole_str = "";
	whole_str = get_whole_str_from_read(fd, whole_str, line_size);
	printf("whole###########\n%s\n", whole_str);
	printf("linesize    %zu\n", *line_size);
	line = get_one_line(whole_str, line_size);
	printf("line###########\n%s\n", line);
	// whole_str = get_next_whole_str(whole_str);
	return (line);
}

//////////////////////////////////////////// test function
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
	printf("main###########\n%s\n", result);

//	result = get_next_line(fd1);
//	printf("%s\n", result);

	free(result);
	close(fd1);
	return (0);
}
