#include "philosophers.h"

int check_eating(t_philo *philo)
{
	if (philo->eating_counter == philo->input_data->num_of_t_to_eat)
	{
		return (1);
	}
	return (0);
}

void *check_deading(t_philo *philo)
{
	time_t tmp;

	tmp = philo->input_data->t_to_die;
	while (1)
	{
		if (check_eating(philo))
			sem_post(g_lifecheck_sem);
			//exit(philo->num_of_philo);
		if (get_time() / 1000 - philo->eat_time > tmp)
		{
			int i = 0;
			philo_death(philo);
			while (i++ < philo->input_data->ph_count)
				sem_post(g_lifecheck_sem);
			//sem_post(g_lifecheck_sem);
			//exit(philo->num_of_philo);
		}
		my_usleep(1000);
	}
	return (NULL);
}

void kill_processes(t_philo *mass, pid_t ret)
{
	int i;
	int count;

	i = 0;
	count = mass[i].input_data->ph_count;
	(void)ret;
	while (i < count)
	{
		write(2, "ee\n", 3);
			printf("%d %d\n", g_status, i);
			write(2, "dd\n", 3);
			kill(mass[i].ret, 0);
		i++;
	}
	kill(ret, 0);
	sem_wait(g_print_sem);
//	sem_close(g_print_sem);
//	sem_close(g_forks_sem);
	exit (0);
}