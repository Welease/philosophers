#include "philosophers.h"

time_t get_time()
{
	const time_t s_to_ms = 1000000;
	time_t tmp1;
	suseconds_t tmp;
	t_time_sturct tv;
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


char *get_message(char *message, t_philo *philo, size_t *len_of)
{
	size_t len;
	size_t len_tmp;
	size_t tmp_len;
	char *tmp;
	char *result;
	len = 6;
	tmp = ft_itoa((philo->num_of_philo) + 1);
	tmp_len = ft_strlen(tmp);
	len += tmp_len;
	len_tmp = ft_strlen(message);
	len += len_tmp;
	result = (char *)malloc(len + 1);
	int i = 0;
	int j = 0;
	while (i < 6)
		result[i++] = ' ';
	while (j < (int)tmp_len)
		result[i++] = tmp[j++];
	j = 0;
	while (j < (int)len_tmp)
		result[i++] = message[j++];
	*len_of = len;
	free(tmp);
	return (result);
}

void print_message(t_philo *philo, char *message, int is_dead)
{
	char *tmp;
	size_t len;
	tmp = get_message(message, philo, &len);
	sem_wait(g_print_sem);
	ft_putnbr_fd((get_time()) / 1000, 1);
	write(1, tmp, len);
	if (!is_dead)
		sem_post(g_print_sem);
	free(tmp);
}


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

void put_forks(t_philo *philo)
{
	(void)philo;
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

void eating(t_philo *philo)
{
	try_to_take_forks(philo);
	print_message(philo, " is eating\n", 0);
	//sem_wait(philo->life_check_sem);
	philo->eat_time = get_time() / 1000;
	my_usleep(philo->input_data->t_to_eat * 1000);
	philo->eating_counter++;
	//sem_post(philo->life_check_sem);
	put_forks(philo);
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