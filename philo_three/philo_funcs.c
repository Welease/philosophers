#include "philosophers.h"
int try_to_take_forks(t_philo *philo)
{
	sem_wait(g_waiter);
	sem_wait(g_forks_sem);
	print_message(philo, " has taken a fork\n", 0);
	sem_wait(g_forks_sem);
	print_message(philo, " has taken a fork\n", 0);
	sem_post(g_waiter);
	return (0);
}

void put_forks()
{
	sem_post(g_forks_sem);
	usleep(5);
	sem_post(g_forks_sem);
	usleep(5);
}

void philo_death(t_philo *philo)
{
	print_message(philo, " is dead\n", 1);
}

void thinking(t_philo *philo)
{
	print_message(philo, " is thinking\n", 0);
}

void sleeping(t_philo *philo)
{
	print_message(philo,  " is sleeping\n", 0);
	my_usleep(philo->input_data->t_to_sleep * 1000);
}
