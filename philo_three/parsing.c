#include "philosophers.h"

int pars_argv(char **argv, int flag, t_input_data *input)
{
	long long tmp;
	int 		i;

	i = 1;
	while (i < 6)
	{
		tmp = ft_atoll(argv[i]);
		if (tmp < 0)
			return (-1);
		if (i == 1 && (tmp > INT_MAX || (input->ph_count = (int)tmp) == 0))
			return (-1);
		i == 2 ? input->t_to_die = (time_t)tmp : 0;
		i == 3 ? input->t_to_eat = (time_t)tmp : 0;
		i == 4 ? input->t_to_sleep = (time_t)tmp : 0;
		if (i == 4 && !flag)
		{
			input->num_of_t_to_eat = INT_MAX;
			break;
		}
		if (i == 5 && (tmp > INT_MAX || (input->num_of_t_to_eat = (int)tmp) == 0))
			return (-1);
		i++;
	}
	return (0);
}