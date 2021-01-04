#include "utils.h"
#include "philosophers.h"
#include <time.h>

static int	checkspace(char *str)
{
	if (*str == ' ' ||
		*str == '\t' ||
		*str == '\n' ||
		*str == '\v' ||
		*str == '\f' ||
		*str == '\r')
		return (1);
	return (0);
}

long long			ft_atoll(char *str)
{
	long long	res;

	res = 0;
	while (checkspace(str))
		str++;
	if (*str == '-')
		return (-1);
	while ((*str >= '0') && (*str <= '9') && *str)
	{
		res = res * 10 + *str - 48;
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (res);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

void    ft_putnbr_fd(time_t n, int fd)
{
	unsigned char tmp;

	if (n / 10)
		ft_putnbr_fd(n / 10, fd);
	tmp = (unsigned char)(n % 10) + '0';
	write(fd, &tmp, 1);
}

void my_usleep(suseconds_t time)
{
	time_struct tmp1;
	time_struct tmp2;

	gettimeofday(&tmp1, NULL);
	gettimeofday(&tmp2, NULL);
	while (tmp2.tv_sec * 1000000 + tmp2.tv_usec - tmp1.tv_sec * 1000000 - tmp1.tv_usec <= time)
	{
		usleep(10);
		gettimeofday(&tmp2, NULL);
	}
}

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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	if (dstsize && i < dstsize - 1)
		i = i + ft_strlcpy(dst + i, src, dstsize - i);
	else
		i = i + ft_strlen(src);
	return (i);
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