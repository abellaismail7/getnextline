#include <stddef.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
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
	return (str);
}

int	is_line(char *str, int size)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	if (size == 0)
		return (ft_strlen(str));
	return (0);
}

char	*get_line(char **s, int len)
{
	char	*str;

	if (len == 0)
		return (0);
	str = malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, *s, len + 1);
	**s = 0;
	*s = ft_strjoin(*s,*s + len);
	return (str);
}
