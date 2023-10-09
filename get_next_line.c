/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:58:34 by yliu              #+#    #+#             */
/*   Updated: 2023/10/09 17:11:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*str;
	int			i;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (str == NULL)
		return (NULL);
	i = read(fd, str, BUFFER_SIZE);
	if (i == -1)
		return (free(str), NULL);
	return (str);
}

// test function
int	main(void)
{
	int		fd1;
	char	*result;

	// fd1 = open("empty.txt", O_RDONLY);
	fd1 = open("test.txt", O_RDONLY);
	if (fd1 == -1)
		return (0);
	result = get_next_line(fd1);
	printf("%s\n", result);

	// result = get_next_line(fd1);
	// printf("%s\n", result);

	free(result);
	close(fd1);
	return (0);
}