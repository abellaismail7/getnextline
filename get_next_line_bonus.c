/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:23:38 by iait-bel          #+#    #+#             */
/*   Updated: 2021/11/24 18:23:38 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int	ft_free(void *p)
{
	free(p);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str[4096] = {0};
	int			size;
	int			index;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == 0)
		return (0);
	while (1)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1 || (size == 0 && str[fd] == 0))
			break ;
		if (size == 0 && str[fd] && *str[fd] == 0 && ft_free(str[fd]))
			break ;
		buf[size] = 0;
		str[fd] = ft_strjoin(str[fd], buf);
		index = is_line(str[fd], size);
		if (index && ft_free(buf))
			return (get_line(str + fd, index));
	}
	free(buf);
	return (0);
}
