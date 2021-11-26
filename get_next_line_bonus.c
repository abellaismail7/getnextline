
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


int ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	if (src == 0 || size == 0)
		return ;
	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return ;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(str + s1_len, s2, s2_len + 1);	
	free(s1);
	return str;
}

int is_line(char *str)
{
	int i = 0;

	while(str[i])
	{
		if(str[i] == '\n')
			return i + 1;
		i++;
	}
	return 0;
}

char * get_line(char **s, int len)
{
	char *str;

	if(len == 0)
		return 0;
	str =  malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return 0;
	ft_strlcpy(str, *s, len + 1);
	**s = 0;
	*s = ft_strjoin(*s,*s + len);
	return str;
}

char *get_next_line(int fd)
{
	char *buf;
	static char *str[4096] = {0};
	int size;
	int index;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == 0)
		return 0;
	while(1)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if(size == -1)
			break ;
		if(size == 0)
		{
			if(!str[fd])
				break;	
			else if(str[fd] && *str == 0)
			{
				free(str[fd]);
				break;
			}
		}
		buf[size] = 0;
		str[fd] = ft_strjoin(str[fd], buf);
		index = is_line(str[fd]);
		if (size == 0 && index == 0)
			index = ft_strlen(str[fd]);
		if(index)
		{
			free(buf);
			return get_line(str + fd, index);
		}
	}
	free(buf);
	return 0;
}

//#include<fcntl.h>
//#include<unistd.h>
//
//int main()
//{
//	int fd = open("test.txt", O_RDONLY | O_CREAT);
//	char * str;
//	while((str = get_next_line(fd)))
//	{
//		write(1, ">>", 2);
//		write(1, str, ft_strlen(str));
//	}
//}
