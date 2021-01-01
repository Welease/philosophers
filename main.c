#include "philosophers.h"

int pars_argv(char **argv, int flag)
{
	long long tmp;
	int 		i;

	i = 1;
	while (i < 6)
	{
		tmp = ft_atoll(argv[i]);
		if (tmp < 0)
			return (-1);
		if (i == 1 && (tmp > INT_MAX || (g_ph_count = (int)tmp) == 0))
			return (-1);
		i == 2 ? g_t_to_die = (time_t)tmp : 0;
		i == 3 ? g_t_to_eat = (time_t)tmp : 0;
		i == 4 ? g_t_to_sleep = (time_t)tmp : 0;
		if (i == 4 && !flag)
			break;
		if (i == 5 && (tmp > INT_MAX || (g_num_of_t_to_eat = (int)tmp) == 0))
			return (-1);
		i++;
	}
	printf("%d %lu %lu %lu %d\n", g_ph_count, g_t_to_die, g_t_to_eat, g_t_to_sleep, g_num_of_t_to_eat);
}

int start(char **argv, int flag)
{
	if (pars_argv(argv, 1) == -1)
		return (-1);
}

int main(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		write(1, "Wrong count of arguments\n", 26);
		return (0);
	}
	else if ((argc == 5 && start(argv, 0) == -1) || (argc == 6 && start(argv, 1) == -1))
	{
		write(1, "Invalid paramaters\n", 20);
		return (0);
	}
}