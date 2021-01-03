#include "philosophers.h"

void forks_mass_init(t_input_data *input_data)
{
	int i;

	i = 0;
	while (i < input_data->ph_count)
		pthread_mutex_init(&g_forks_mass[i++], NULL);
}

t_input_data *get_copy_of_data(t_input_data *input_data)
{
	t_input_data *tmp;

	tmp = (t_input_data *)malloc(sizeof(t_input_data));
	tmp->t_to_eat = input_data->t_to_eat;
	tmp->t_to_die = input_data->t_to_die;
	tmp->num_of_t_to_eat = input_data->num_of_t_to_eat;
	tmp->ph_count = input_data->ph_count;
	tmp->t_to_sleep = input_data->t_to_sleep;
	return (tmp);
}

void fill_mass_of_philo(t_philo *philo_mass, t_input_data *input_data)
{
	int fork_index;
	int i;

	i = 0;
	t_input_data tmp;
	while (i < input_data->ph_count)
	{
		if ((fork_index = i - 1) < 0)
			fork_index = input_data->ph_count - 1;
		philo_mass[i].num_of_philo = i;
		philo_mass[i].l_fork = &g_forks_mass[fork_index];
		philo_mass[i].r_fork = &g_forks_mass[i];
		philo_mass[i].life_time = input_data->t_to_die * 1000;
		philo_mass[i].has_eated = 0;
		philo_mass[i].eating_counter = 0;
		philo_mass[i].input_data = get_copy_of_data(input_data);
		i++;
	}
}

void *kill_all(t_philo *mass)
{
	int i;
	int ph_c;

	i = 0;
	ph_c = mass[0].input_data->ph_count;
	while (i < ph_c)
	{
		free(mass[i].input_data);
		pthread_mutex_destroy(&(g_forks_mass[i++]));
	}
	free(g_forks_mass);
	free(mass);
	pthread_mutex_destroy(&g_print_mutex);
	pthread_mutex_destroy(&g_lifecheck_mutex);
	pthread_mutex_destroy(&g_tmp_mutex);
	return (NULL);
}

int check_all_eating(t_philo *mass)
{
	int ret;
	int i;

	i =  0;
	ret = 0;
	while (i < mass[0].input_data->ph_count)
	{
		pthread_mutex_lock(&g_tmp_mutex);
		if (mass[i].eating_counter >= mass[0].input_data->num_of_t_to_eat)
			ret++;
		pthread_mutex_unlock(&g_tmp_mutex);
		i++;
	}
	if (ret == mass[0].input_data->ph_count)
		return (1);
	return (0);
}

void *check_deading(t_philo *mass)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < mass[0].input_data->ph_count)
		{
			pthread_mutex_lock(&g_lifecheck_mutex);
			mass[i].life_time -= 1000;
			pthread_mutex_unlock(&g_lifecheck_mutex);
			if (check_all_eating(mass))
				return (kill_all(mass));
			if ((mass[i].life_time < 0))
			{
				philo_death(mass + i);
				return (kill_all(mass));
			}
			i++;
		}
		my_usleep(1000);
	}
	return (NULL);
}

int init_threads(t_philo *philo_mass, t_input_data *input_data, pthread_t g_death_thread)
{
	int i;

	i = 0;
	while (i < input_data->ph_count)
	{
		if (pthread_create(&((philo_mass[i]).philo_thread), NULL, (void * (*)(void *))simulation_start, ((void *)(philo_mass + i))))
			return (-1);
		i++;
	}
	if (pthread_create(&g_death_thread, NULL, (void * (*)(void *))check_deading, ((void *)(philo_mass))))
		return (-1);
	g_start_flag = 1;
	pthread_join(g_death_thread, NULL);
	return (0);
}

int start(char **argv, int flag, t_input_data *input_data)
{
	t_philo *philo_mass;
	pthread_t g_death_thread;

	if (pars_argv(argv, flag, input_data) == -1)
		return (-1);
	if (!(g_forks_mass = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * input_data->ph_count)))
	{
		write(1, "mutex error\n", 12);
		return (-1);
	}
	forks_mass_init(input_data);
	philo_mass = (t_philo *)malloc(sizeof(t_philo) * input_data->ph_count);
	fill_mass_of_philo(philo_mass, input_data);
	if ((init_threads(philo_mass, input_data, g_death_thread))  == -1)
	{
		write(1, "thread error\n", 13);
		return (-1);
	}
	return (0);
}