#include "philosophers.h"

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


char *generation_of_str(int i)
{
	char *tmp;

	tmp = ft_itoa(i);
	return (tmp);
}

void fill_mass_of_philo(t_philo *philo_mass, t_input_data *input_data)
{
	char *sem_name;
	int fork_index;
	int i;

	i = 0;
	t_input_data tmp;
	while (i < input_data->ph_count)
	{
		if ((fork_index = i - 1) < 0)
			fork_index = input_data->ph_count - 1;
		philo_mass[i].num_of_philo = i;
		philo_mass[i].eating_counter = 0;
		sem_name = generation_of_str(i + 1);
		sem_unlink(sem_name);
		if ((philo_mass[i].life_check_sem = sem_open(sem_name,  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
			return;
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
		sem_close(mass[i].life_check_sem);
		free(mass[i].input_data);
		i++;
	}
	free(mass);
	sem_close(g_print_mutex);
	sem_close(g_lifecheck_mutex);
	sem_close(g_tmp_mutex);
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
		sem_wait(g_tmp_mutex);
		if (mass[i].eating_counter >= mass[0].input_data->num_of_t_to_eat)
			ret++;
		sem_post(g_tmp_mutex);
		i++;
	}
	if (ret == mass[0].input_data->ph_count)
		return (1);
	return (0);
}

void *check_deading(t_philo *mass)
{
	int i;
	time_t tmp;
	int ph_counter;
	tmp = mass[0].input_data->t_to_die;
	ph_counter = mass[0].input_data->ph_count;
	while (!g_start_flag)
		;
	while (1)
	{
		i = 0;
		while (i < ph_counter)
		{
			sem_wait(mass[i].life_check_sem);
			if (check_all_eating(mass))
				return (kill_all(mass));
			if (get_time() / 1000 - mass[i].eat_time > tmp)
			{
				philo_death(mass + i);
				return (kill_all(mass));
			}
			sem_post(mass[i].life_check_sem);
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
	sem_unlink("/printingsem");
	sem_unlink("/waitersem");
	sem_unlink("/forksem");
	if ((g_print_sem = sem_open("/printingsem",  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED ||
		(g_waiter = sem_open("/waitersem",  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED ||
		(g_forks_sem = sem_open("/forksem",  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, input_data->ph_count)) == SEM_FAILED)
	{
		write(1, "sem error\n", 10);
		return (-1);
	}
	philo_mass = (t_philo *)malloc(sizeof(t_philo) * input_data->ph_count);
	fill_mass_of_philo(philo_mass, input_data);
	if ((init_threads(philo_mass, input_data, g_death_thread))  == -1)
	{
		write(1, "thread error\n", 13);
		return (-1);
	}
	return (0);
}