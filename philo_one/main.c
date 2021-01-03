#include "philosophers.h"

time_t get_time()
{
	time_t tmp1;
	suseconds_t tmp;
	time_struct tv;
	if (gettimeofday(&tv, NULL) == -1)
		return NULL;
	tmp1 = tv.tv_sec - g_tv.tv_sec;
	tmp = tv.tv_usec - g_tv.tv_usec;
	if (tmp < 0)
	{
		tmp1 -= 1;
		tmp += 1000000;
	}
	if (tmp1 > 0)
	{
		tmp += tmp1 * 1000000;
	}
	return (tmp);
}

void print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&g_print_mutex);
	ft_putnbr_fd((get_time()) / 1000, 1);
	write(1, "    ", 6);
	ft_putnbr_fd((time_t)(philo->num_of_philo) + 1, 1);
	//write(1, "      ", 4);
	//ft_putnbr_fd(philo->life_time / 1000, 1);
	write(1, message, ft_strlen(message));
	pthread_mutex_unlock(&g_print_mutex);
}


int try_to_take_forks(t_philo *philo)
{
	if (philo->num_of_philo % 2)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message(philo,  " has taken a left fork\n");
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, " has taken a right fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(philo,  " has taken a right fork\n");
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, " has taken a left fork\n");
	}
	if (philo->r_fork && philo->l_fork)
		return (1);
	return (0);
}

void put_forks(t_philo *philo)
{
	if (philo->num_of_philo % 2)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void philo_death(t_philo *philo)
{
	print_message(philo, " is dead\n");
}

void thinking(t_philo *philo)
{
	print_message(philo, " is thinking\n");
}

void sleeping(t_philo *philo)
{
	print_message(philo,  " is sleeping\n");
	my_usleep(g_t_to_sleep * 1000);
}

void eating(t_philo *philo)
{
	try_to_take_forks(philo);
	print_message(philo, " is eating\n");
	philo->life_time = g_t_to_die * 1000;
	my_usleep(g_t_to_eat * 1000);
	philo->has_eated = 1;
	philo->eating_counter++;
	put_forks(philo);
}

void *simulation_start(t_philo *philo)
{
	while (!g_start_flag)
		;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->eating_counter == g_num_of_t_to_eat)
			break;
	}
	while (1);
	return (NULL);
}


int main(int argc, char **argv)
{
	pthread_mutex_init(&g_print_mutex, NULL);
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
	else if ((argc == 5 && start(argv, 0) == -1) || (argc == 6 && start(argv, 1) == -1))
	{
		write(1, "Invalid paramaters\n", 20);
		return (0);
	}
}