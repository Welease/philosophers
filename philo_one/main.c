#include "philosophers.h"

time_t get_time()
{
	const time_t s_to_ms = 1000000;
	time_t tmp1;
	suseconds_t tmp;
	time_struct tv;
	if (gettimeofday(&tv, NULL) == -1)
		return 0;
	tmp1 = tv.tv_sec - g_tv.tv_sec;
	tmp = tv.tv_usec - g_tv.tv_usec;
	if (tmp < 0)
	{
		tmp1--;
		tmp += s_to_ms;
	}
	if (tmp1 > 0)
		tmp += tmp1 * s_to_ms;
	return (tmp);
}

void print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&g_print_mutex);
	ft_putnbr_fd((get_time()) / 1000, 1);
	write(1, "    ", 6);
	ft_putnbr_fd((time_t)(philo->num_of_philo) + 1, 1);
	write(1, message, ft_strlen(message));
	if (ft_strncmp(message, " is dead\n", 9))
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
	return (0);
}

void put_forks(t_philo *philo)
{
	if (philo->num_of_philo % 2)
	{
		pthread_mutex_unlock(philo->r_fork);
		usleep(5);
		pthread_mutex_unlock(philo->l_fork);
		usleep(5);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		usleep(5);
		pthread_mutex_unlock(philo->r_fork);
		usleep(5);
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
	my_usleep(philo->input_data->t_to_sleep * 1000);
}

void eating(t_philo *philo)
{
	try_to_take_forks(philo);
	print_message(philo, " is eating\n");
	pthread_mutex_lock(&(philo->life_check_mutex));
	philo->eat_time = get_time() / 1000;
	pthread_mutex_unlock(&(philo->life_check_mutex));
	my_usleep(philo->input_data->t_to_eat * 1000);
	pthread_mutex_lock(&g_tmp_mutex);
	philo->eating_counter++;
	pthread_mutex_unlock(&g_tmp_mutex);
	put_forks(philo);
}

void *simulation_start(t_philo *philo)
{
	while (!g_start_flag)
		;
	philo->eat_time = get_time() / 1000;
	pthread_detach(philo->philo_thread);
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

	pthread_mutex_init(&g_print_mutex, NULL);
	pthread_mutex_init(&g_tmp_mutex, NULL);
	pthread_mutex_init(&g_lifecheck_mutex, NULL);
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