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

	tmp = *lst;
	while (tmp)
	{
		if (tmp->content_size == fd)
		{
			printf("%i found\n", fd);
			return (tmp);
		}
		tmp = tmp->next;
	}
	// ft_lstaddend(lst, ft_lstnew("", fd));
	tmp = ft_lstnew("", fd);
	// printf("%s\n", tmp->content);
	return (tmp);
}

void	lst_show(t_list *lst)
{
	printf("\n");
	while (lst)
	{
		printf("%zu '%s'\n", lst->content_size, lst->content);
		lst = lst->next;
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*elem;
	static char		*reserve;
	char			buf[BUFF_SIZE];
	void			*tmp;
	void			*bufend;

	elem = find_elem(&lst, fd);
	reserve = elem->content;
	if (fd < 0 || read(fd, buf, 0) == -1)
		return (-1);
	// if (reserve == 0)
		// reserve = ft_strdup("");
	while (!ft_strchr(reserve, '\n'))
	{
		ft_bzero(buf, BUFF_SIZE);
		read(fd, buf, BUFF_SIZE);
		if (buf[0] == '\0' && reserve[0] == '\0')
			return (0);
		if (buf[0] == '\0')
		{
			*line = reserve;
			ft_memdel((void*)&reserve);
			return (1);
		}
		tmp = reserve;
		bufend = ft_strsub(buf, 0, BUFF_SIZE);
		reserve = ft_strjoin(reserve, bufend);
		// ft_memdel(&tmp);
		// ft_memdel(&bufend);
		// printf("reserve: '%s'\n", reserve);
	}
	*line = ft_strsub(reserve, 0, ft_strchr(reserve, '\n') - reserve);
	tmp = reserve;
	reserve = ft_strsub(reserve, ft_strchr(reserve, '\n') - reserve + 1,
		ft_strlen(reserve) - (ft_strchr(reserve, '\n') - reserve) - 1);
	// ft_memdel(&tmp);
	return (1);
}

int		main(void)
{
	char *line;

	int fd1 = open("test", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);
	int fd3 = open("test3", O_RDONLY);
	// get_next_line(fd, &line);
	int i = -1;
	while (++i < 5)
	{
		printf("res: %i line: %s\n", get_next_line(fd1, &line), line);
		ft_memdel((void*)&line);
	}
	// system("leaks a.out");
	return (0);
}



// int		main(void)
// {
// 	t_list *lst;
// 	lst = 0;

// 	find_elem(&lst, 1);
// 	find_elem(&lst, 2);
// 	find_elem(&lst, 1);
// 	find_elem(&lst, 3);
// 	find_elem(&lst, 1);
// 	lst_show(lst);
// 	return (0);
// }
