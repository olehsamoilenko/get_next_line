/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:44:50 by osamoile          #+#    #+#             */
/*   Updated: 2018/04/17 13:44:53 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

void	lst_show(t_list *tmp)
{
	printf("LIST:\n");
	while (tmp)
	{
		printf("%zu '%s'\n", tmp->content_size, tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
}

// int		main(void)
// {
// 	char *line;

// 	int fd = 0;
// 	write(fd, "abc\n\n", 5);
// 	// int fd1 = open("test", O_RDONLY);
// 	// int fd2 = open("test2", O_RDONLY);
// 	// int fd3 = open("test3", O_RDONLY);

// 	// int i = -1;
// 	// while (++i < 10)
// 	// {
// 		printf("res: %i line: %s\n", get_next_line(0, &line), line);
// 		ft_strdel(&line);
// 		// printf("res: %i line: %s\n", get_next_line(fd1, &line), line);
// 		// ft_strdel(&line);
// 		// printf("res: %i line: %s\n", get_next_line(fd2, &line), line);
// 		// ft_strdel(&line);
// 		// printf("res: %i line: %s\n", get_next_line(fd3, &line), line);
// 		// ft_strdel(&line);
// 		// printf("res: %i line: %s\n", get_next_line(fd3, &line), line);
// 		// ft_strdel(&line);

// 		// printf("res: %i line: %s\n", get_next_line(0, &line), line);
// 		// ft_strdel(&line);
// 	// }
// 	// system("leaks a.out");
// 	return (0);
// }

int main(void)
{
char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	printf("%i\n", strcmp(line, "abcd"));
	printf("%c\n", line[5]);
	get_next_line(p[0], &line);
	printf("%i\n", strcmp(line, "efgh"));
	printf("%c\n", line[6]);
	ret = get_next_line(p[0], &line);
	printf("%i\n", ret);
}
