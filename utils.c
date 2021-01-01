#include "utils.h"
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