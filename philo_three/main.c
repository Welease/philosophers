#include "philosophers.h"

void eating(t_philo *philo)
{
	try_to_take_forks(philo);
	print_message(philo, " is eating\n", 0);
	philo->eat_time = get_time() / 1000;
	my_usleep(philo->input_data->t_to_eat * 1000);
	philo->eating_counter++;
	put_forks();
}



void *simulation_start(t_philo *philo)
{
	philo->eat_time = get_time() / 1000;
	pthread_create(&philo->death_thread, NULL, (void * (*)(void *))check_deading, ((void *)(philo)));
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}


int main(int argc, char **argv)
{
	t_input_data input_data;

	if (gettimeofday(&g_tv, NULL) == -1)
	{
		write(1, "some problem with gettimeofday func\n", 37);
		return (0);
	}
	if (argc > 6 || argc < 5)
	{
		write(1, "Wrong count of arguments\n", 26);
		return (0);
	}
	else if ((argc == 5 && start(argv, 0, &input_data) == -1) || (argc == 6 && start(argv, 1, &input_data) == -1))
	{
		write(1, "Invalid paramaters\n", 20);
		return (0);
	}
}