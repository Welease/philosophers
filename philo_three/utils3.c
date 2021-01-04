#include "philosophers.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (src == NULL)
		return (0);
	if (dstsize == 0 || dst == NULL)
		return (ft_strlen(src));
	while (i < (dstsize - 1))
	{
		*(dst + i) = *(src + i);
		if (*(src + i) == '\0')
			return (ft_strlen(src));
		i++;
	}
	*(dst + i) = '\0';
	return (ft_strlen(src));
}

static void			add_nbr(int n, char *m, int i)
{
	long long int	a;

	a = n;
	if (a / 10)
		add_nbr(a / 10, m, i - 1);
	m[i] = a % 10 + '0';
}

static char			*if_negative(char *res, int n)
{
	while (n)
	{
		res[n] = res[n - 1];
		n--;
	}
	res[0] = '-';
	return (res);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (!s1[i] && !s2[i])
			break ;
		if (((unsigned char*)s1)[i] != ((unsigned char*)s2)[i])
			return ((int)(((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]));
		i++;
	}
	return (0);
}

char				*ft_itoa(int n)
{
	int				i;
	int				tmp;
	char			*res;

	i = 0;
	tmp = n;
	while (n)
	{
		n = n / 10;
		i++;
	}
	if ((res = (char *)malloc(i + 2)) == NULL)
		return (NULL);
	res[i + 1] = '\0';
	res[i] = '\0';
	add_nbr(tmp > 0 ? tmp : tmp * -1, res, i - 1);
	if (tmp < 0)
		return (if_negative(res, i));
	return (res);
}
