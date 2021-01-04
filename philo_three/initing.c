#include "philosophers.h"

void check_num_of_eat(t_philo *philo_mass)
{
	int i;

	i = 0;
	sem_wait(g_lifecheck_sem);
	while (i < philo_mass[0].input_data->ph_count)
	{
		sem_wait(philo_mass[i].eat_sem_count);
		i++;
	}
	exit (-1);
}

int init_threads(t_philo *philo_mass, t_input_data *input_data)
{
	pid_t ret;
	int i;

	i = 0;
	ret = 0;
	while (i < input_data->ph_count)
	{
		if ((philo_mass[i].ret = fork()) == -1)
			return (-1);
		if (philo_mass[i].ret == 0)
			simulation_start(philo_mass + i);
		i++;
	}
	if (input_data->num_of_t_to_eat < INT_MAX)
	{
		if ((ret = fork()) == -1)
			return (-1);
		if (ret == 0)
			check_num_of_eat(philo_mass);
	}
	waitpid(-1, &g_status, 0);
	kill_processes(philo_mass);
	return (0);
}

int start(char **argv, int flag, t_input_data *input_data)
{
	t_philo *philo_mass;

	if (pars_argv(argv, flag, input_data) == -1)
		return (-1);
	sem_unlink("/printingsem");
	sem_unlink("/waitersem");
	sem_unlink("/forksem");
	sem_unlink("/lifesem");
	if ((g_print_sem = sem_open("/printingsem",  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED ||
		(g_waiter = sem_open("/waitersem",  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED ||
		(g_forks_sem = sem_open("/forksem",  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, input_data->ph_count)) == SEM_FAILED ||
			(g_lifecheck_sem = sem_open("/lifesem", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
	{
		write(1, "sem error\n", 10);
		return (-1);
	}
	sem_wait(g_lifecheck_sem);
	if (!(philo_mass = (t_philo *)malloc(sizeof(t_philo) * input_data->ph_count)))
		return (-1);
	fill_mass_of_philo(philo_mass, input_data);
	if ((init_threads(philo_mass, input_data))  == -1)
	{
		write(1, "thread error\n", 13);
		return (-1);
	}
	return (0);
}