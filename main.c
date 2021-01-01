#include "philosophers.h"

void print_message(t_philo *philo)
{
	time_struct tv;
	if (gettimeofday(&tv, NULL) == -1)
		return ;
	printf("%d ", (tv.tv_usec - g_tv.tv_usec) * 1000);
	write (1, &philo->num_of_philo, 1); //TODO make nbyte == count of dis in num of philo
	if (philo->l_fork)
		write(1, " has taken a left fork\n", 23);
	else if (philo->r_fork)
		write(1, " has taken a right fork\n", 23);
	else if (philo->eating_flag)
		write(1, " is eating\n", 11);
	else if (philo->sleeping_flag)
		write(1, " is sleeping\n", 14);
	else if (philo->thinking_flag)
		write(1, " is thinking\n", 14);
}

void fill_forks_mass_by_zero()
{
	int i;

	i = 0;
	while (i < g_ph_count)
		g_forks_mass[i++] = 0;
}

void fill_mass_of_philo(t_philo *philo_mass)
{
	int i;

	i = 0;
	while (i < g_ph_count)
	{
		(philo_mass[i]).num_of_philo = i;
		(philo_mass)[i].l_fork = 0;
		(philo_mass)[i].r_fork = 0;
		(philo_mass)[i].life_time = 0;
		(philo_mass)[i].eating_flag = 0;
		(philo_mass)[i].sleeping_flag = 0;
		(philo_mass)[i].thinking_flag = 0;
		i++;
	}
}

int try_to_take_forks(t_philo *philo)
{
	int i;
	if (philo->num_of_philo % 2)
	{
		if (!g_forks_mass[philo->num_of_philo])
		{
			g_forks_mass[philo->num_of_philo] = 1;
			philo->l_fork = 1;
		}
		if ((i = philo->num_of_philo + 1) > g_ph_count - 1)
			i = 0;

		if (!g_forks_mass[i])
		{
			g_forks_mass[i] = 1;
			philo->r_fork = 1;
		}
	}
	else
	{
		i = philo->num_of_philo - 1;
		if (i < 0)
			i = g_ph_count - 1;
		if (!g_forks_mass[i])
		{
			g_forks_mass[i] = 1;
			philo->r_fork = 1;
		}
		if (!g_forks_mass[philo->num_of_philo])
		{
			g_forks_mass[philo->num_of_philo] = 1;
			philo->l_fork = 1;
		}
	}
	if (philo->r_fork && philo->l_fork)
		return (1);
	return (0);
}

void put_forks(t_philo *philo)
{
	int i;
	if (philo->num_of_philo % 2)
	{
		g_forks_mass[philo->num_of_philo] = 0;
		philo->l_fork = 0;
		if ((i = philo->num_of_philo + 1) > g_ph_count - 1)
			i = 0;
		g_forks_mass[i] = 0;
		philo->r_fork = 0;
	}
	else
	{
		i = philo->num_of_philo - 1;
		if (i < 0)
			i = g_ph_count - 1;
		g_forks_mass[i] = 0;
		philo->r_fork = 0;
		g_forks_mass[philo->num_of_philo] = 0;
		philo->l_fork = 0;
	}
}

void thinking(t_philo *philo)
{
	philo->thinking_flag = 1;
	print_message(philo);
	philo->thinking_flag = 0;
	eating(philo);
}

void sleeping(t_philo *philo)
{
	print_message(philo);
	philo->sleeping_flag = 0;
	thinking(philo);
}

void *eating(t_philo *philo)
{
	if (try_to_take_forks(philo))
	{
		philo->eating_flag = 1;
		pthread_mutex_lock(&eat_mutex);
		print_message(philo);
		usleep(g_t_to_eat * 1000);
		pthread_mutex_unlock(&eat_mutex);
		philo->eating_flag = 0;
		philo->sleeping_flag = 1;
		put_forks(philo);
		sleeping(philo);
	}
	else
		eating(philo);
	return (NULL);
}

int init_threads(t_philo *philo_mass)
{
	int i;

	i = 0;
	while (i < g_ph_count)
	{
		if (pthread_create(&philo_mass[i].philo_thread, NULL, (void * (*)(void *))eating, ((void *)(philo_mass + i))))
			return (-1);
		usleep(2000);
		//TODO selfmade usleep
		i++;
	}
	return (0);
}

int start(char **argv, int flag)
{
	t_philo *philo_mass;
	if (pars_argv(argv, 1) == -1)
		return (-1);
	g_forks_mass = (int *)malloc(g_ph_count);
	fill_forks_mass_by_zero();
	philo_mass = (t_philo *)malloc(sizeof(t_philo) * g_ph_count);
	fill_mass_of_philo(philo_mass);
	init_threads(philo_mass);
}

int main(int argc, char **argv)
{
	if (pthread_mutex_init(&eat_mutex, NULL))
		return (0);
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