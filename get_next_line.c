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
	static char		*reserve;
	char			buf[BUFF_SIZE];
	void			*tmp;
	void			*bufend;

	if (fd < 0 || read(fd, buf, 0) == -1)
		return (-1);
	reserve = ft_strdup("");
	while (!ft_strchr(reserve, '\n'))
	{
		ft_bzero(buf, BUFF_SIZE);
		read(fd, buf, BUFF_SIZE);
		if (buf[0] == '\0')
			return (0);
		tmp = reserve;
		bufend = ft_strsub(buf, 0, BUFF_SIZE);
		reserve = ft_strjoin(reserve, bufend);
		ft_memdel(&tmp);
		ft_memdel(&bufend);
	}
	// printf("%zu\n", ft_strlen(reserve));
	// ft_putnbr(ft_strlen(reserve));
	// ft_putchar('\n');
	// ft_putstr(reserve);

	*line = ft_strsub(reserve, 0, ft_strchr(reserve, '\n') - reserve);
	ft_putstr("\nline: ");
	ft_putstr(*line);
	tmp = reserve;
	int skip = 0;
	if (reserve[0] == '\n')
		skip = 1;
	reserve = ft_strsub(reserve, ft_strchr(reserve, '\n') - reserve + skip,
		ft_strlen(reserve) - (ft_strchr(reserve, '\n') - reserve) - 1);
	ft_memdel(&tmp);
	ft_putstr("\nreserve: ");
	ft_putstr(reserve);
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
	ft_putnbr(get_next_line(fd, &line));
	ft_putstr("\nRESULT: ");
	ft_putstr(line);
	ft_putnbr(get_next_line(fd, &line));
	ft_putstr("\nRESULT: ");
	ft_putstr(line);
	// system("leaks a.out");
	return (0);
}

