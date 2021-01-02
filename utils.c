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
	int i;
	i = 0;
	while (time  - 1000000 >= 0)
	{
		i++;
		time = time - 1000000;
	}
//	printf("%d %d\n", time, i);
	gettimeofday(&tmp2, NULL);
//	printf("%lu\n", tmp2.tv_sec - tmp1.tv_sec);
//	printf("%d\n", tmp2.tv_usec - tmp1.tv_usec);
	while (tmp2.tv_sec - tmp1.tv_sec <= i)
	{
		gettimeofday(&tmp2, NULL);
		if (tmp2.tv_sec - tmp1.tv_sec == i && tmp2.tv_usec - tmp1.tv_usec >= 0)
			break;
	}
}
