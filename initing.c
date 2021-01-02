//
// Created by Wynn Elease on 1/2/21.
//
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
		philo_mass[i].life_time = 0;
		i++;
	}
}

int init_threads(t_philo *philo_mass)
{
	int i;

	i = 0;
	while (i < g_ph_count)
	{
		if (pthread_create(&((philo_mass[i]).philo_thread), NULL, (void * (*)(void *))simulation_start, ((void *)(philo_mass + i))))
			return (-1);
		//usleep(200);
		//TODO selfmade usleep
		i++;
	}
	g_start_flag = 1;
	while (1);
	return (0);
}

int start(char **argv, int flag)
{
	t_philo *philo_mass;
	if (pars_argv(argv, 1) == -1)
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
}