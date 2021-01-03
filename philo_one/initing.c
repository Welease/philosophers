#include "philosophers.h"

void forks_mass_init()
{
	int i;

	i = 0;
	while (i < g_ph_count)
		pthread_mutex_init(&g_forks_mass[i++], NULL);
}

void fill_mass_of_philo(t_philo *philo_mass)
{
	int fork_index;
	int i;

	i = 0;
	while (i < g_ph_count)
	{
		if ((fork_index = i - 1) < 0)
			fork_index = g_ph_count - 1;
		philo_mass[i].num_of_philo = i;
		philo_mass[i].l_fork = &g_forks_mass[fork_index];
		philo_mass[i].r_fork = &g_forks_mass[i];
		philo_mass[i].life_time = g_t_to_die * 1000;
		philo_mass[i].has_eated = 0;
		philo_mass[i].eating_counter = 0;
		i++;
	}
}

void kill_all(t_philo *mass)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&g_print_mutex);
	while (i < g_ph_count)
		pthread_mutex_destroy(&(g_forks_mass[i++]));
	free(g_forks_mass);
	free(mass);
	exit(0);
}

int check_all_eating(t_philo *mass)
{
	int ret;
	int i;

	i =  0;
	ret = 0;
	while (i < g_ph_count)
	{
		if (mass[i].eating_counter == g_num_of_t_to_eat)
			ret++;
		i++;
	}
	if (ret == g_ph_count)
		return (1);
	return (0);
}

void *check_deading(t_philo *mass)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < g_ph_count)
		{
			mass[i].life_time -= 1000;
			if (check_all_eating(mass))
				kill_all(mass);
			if ((mass[i].life_time <= 0))
			{
				philo_death(mass + i);
				kill_all(mass);
			}
			i++;
		}
		my_usleep(1000);
	}
	return (NULL);
}

int init_threads(t_philo *philo_mass)
{
	int i;

	i = 0;
	while (i < g_ph_count)
	{
		if (pthread_create(&((philo_mass[i]).philo_thread), NULL, (void * (*)(void *))simulation_start, ((void *)(philo_mass + i))))
			return (-1);
		i++;
	}
	if (pthread_create(&g_death_thread, NULL, (void * (*)(void *))check_deading, ((void *)(philo_mass))))
		return (-1);
	g_start_flag = 1;
	while (1);
	return (0);
}

int start(char **argv, int flag)
{
	t_philo *philo_mass;
	if (pars_argv(argv, flag) == -1)
		return (-1);
	if (!(g_forks_mass = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_ph_count)))
	{
		write(1, "mutex error\n", 12);
		return (-1);
	}
	forks_mass_init();
	philo_mass = (t_philo *)malloc(sizeof(t_philo) * g_ph_count);
	fill_mass_of_philo(philo_mass);
	if ((init_threads(philo_mass))  == -1)
	{
		write(1, "thread error\n", 13);
		return (-1);
	}
	return (0);
}