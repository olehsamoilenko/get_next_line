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

t_list	*find_elem(t_list **lst, int fd)
{
	t_list *tmp;

	if (*lst == 0)
	{
		*lst = ft_lstnew("", fd);
		return (*lst);
	}
	tmp = *lst;
	while (tmp->next)
	{
		if (tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (tmp->content_size == fd)
		return (tmp);
	tmp->next = ft_lstnew("", fd);
	return (tmp);
}

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

void	cut_content()
{
	
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*elem;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;

	elem = find_elem(&lst, fd);
	// lst_show(lst);
	if (fd < 0 || read(fd, buf, 0) == -1)
		return (-1);
	while (!ft_strchr(elem->content, '\n'))
	{
		ft_bzero(buf, BUFF_SIZE + 1);
		read(fd, buf, BUFF_SIZE);
		if (buf[0] == '\0' && &elem->content[0] == '\0')
			return (0);
		if (buf[0] == '\0')
		{
			*line = elem->content;
			// free(elem);
			return (1);
		}
		tmp = elem->content;
		elem->content = ft_strjoin(elem->content, buf);
		ft_strdel(&tmp);
	}
	*line = ft_strsub(elem->content, 0, ft_strchr(elem->content, '\n') - (char*)elem->content);
	tmp = elem->content;
	elem->content = ft_strsub(elem->content, ft_strchr(elem->content, '\n') - (char*)elem->content + 1,
		ft_strlen(elem->content) - (ft_strchr(elem->content, '\n') - (char*)elem->content) - 1);
	ft_strdel(&tmp);
	// free(elem->content);
	// free(elem);
	// lst_show(lst);
	return (1);
}

int		main(void)
{
	char *line;

	int fd1 = open("test", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);
	int fd3 = open("test3", O_RDONLY);

	// t_list *lst;
	// find_elem(&lst, 5);
	// find_elem(&lst, 4);
	// find_elem(&lst, 5);
	// find_elem(&lst, 4);
	// lst_show(lst);

	int i = -1;
	while (++i < 5)
	{
		printf("res: %i line: %s\n", get_next_line(fd1, &line), line);
		if (ft_strlen(line) != 0)
			free(line);
		printf("res: %i line: %s\n", get_next_line(fd2, &line), line);
		if (ft_strlen(line) != 0)
			free(line);
		printf("res: %i line: %s\n", get_next_line(fd3, &line), line);
		if (ft_strlen(line) != 0)
			free(line);
	}
	system("leaks a.out");
	return (0);
}
