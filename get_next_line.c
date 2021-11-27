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
#include "get_next_line.h"

int	ft_free(void *p)
{
	free(p);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str = 0;
	int			size;
	int			index;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == 0)
		return (0);
	while (1)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1 || (size == 0 && str == 0))
			break ;
		if (size == 0 && str && *str == 0 && ft_free(str))
			break ;
		buf[size] = 0;
		str = ft_strjoin(str, buf);
		index = is_line(str, size);
		if (index && ft_free(buf))
			return (get_line(&str, index));
	}
	free(buf);
	return (0);
}
