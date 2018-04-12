/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:19:24 by osamoile          #+#    #+#             */
/*   Updated: 2018/04/12 16:19:26 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

#include <stdio.h> //trash
#include <fcntl.h> //trash

int		get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE];

	
	while (!ft_strchr(buf, '\n'))
	{
		read(fd, buf, BUFF_SIZE);
		printf("buf: '%s'\n", buf);
	}
	printf("buf contains EOL\n");
	*line = ft_strsub(buf, 0, ft_strchr(buf, '\n') - buf);
	printf("line: '%s' len: %zu\n", *line, ft_strlen(*line));
	if (*line[ft_strlen(*line) + 1] == '\0')
		printf("null-terminator enable\n");
	else
		printf("last char of line: '%c'\n", *line[ft_strlen(*line) + 1]);
	return (1);
}

int		main(int args, char **argv)
{
	char *line = "";
	if (args != 2)
	{
		printf("usage\n");
		return (0);
	}
	int fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	return (0);
}

