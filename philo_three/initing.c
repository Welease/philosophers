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

char *gen_sem_check(int i)
{
	char *ret;
	char *tmp;

	tmp = ft_itoa(i);
	ret = (char *)malloc(ft_strlen(tmp) + 2);
	ft_strlcpy(ret, tmp, ft_strlen(tmp));
	ret[ft_strlen(tmp)] = 'p';
	ret[ft_strlen(tmp) + 1] = '\0';
	write(1, ret, ft_strlen(ret));
	free(tmp);
	return (ret);
}

void fill_mass_of_philo(t_philo *philo_mass, t_input_data *input_data)
{
	char *sem_name;
	char *sem_name1;
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
		sem_name1 = gen_sem_check(i + 1);
		sem_unlink(sem_name);
		sem_unlink(sem_name1);
		if ((philo_mass[i].life_check_sem = sem_open(sem_name,  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
			return;
		philo_mass[i].input_data = get_copy_of_data(input_data);
		if ((philo_mass[i].eat_sem_count = sem_open(sem_name1,  O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
			return;
		sem_wait(philo_mass[i].eat_sem_count);
		i++;
	}
}

int check_eating(t_philo *philo)
{
	if (philo->eating_counter == philo->input_data->num_of_t_to_eat)
	{
		sem_post(philo->eat_sem_count);
		return (1);
	}
	return (0);
}

void *check_deading(t_philo *philo)
{
	int i;
	time_t tmp;
	int ph_counter;
	tmp = philo->input_data->t_to_die;
	ph_counter = philo->input_data->ph_count;
	while (1)
	{
		if (check_eating(philo))
			exit(philo->num_of_philo);
		if (get_time() / 1000 - philo->eat_time > tmp)
		{
			philo_death(philo);
			sem_post(g_lifecheck_sem);
			exit(philo->num_of_philo);
		}
		my_usleep(1000);
	}
	return (NULL);
}

void kill_processes(t_philo *mass, int flag)
{
	int i;
	int count;

	i = 0;
	count = mass[i].input_data->ph_count;

	if (!flag)
	{
		while (i < count)
		{
			if (g_status != i)
				kill(mass[i].ret, 0);
			i++;
		}
	}
	else
	{
		while (i < count)
		{
			//sem_post(mass[i].life_check_sem);
			//sem_close(mass[i].life_check_sem);
			sem_post(mass[i].eat_sem_count);
			sem_close(mass[i].eat_sem_count);
			kill(mass[i].ret, 0);
			i++;
		}
		sem_close(g_print_sem);
		sem_close(g_forks_sem);
	}
}

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
	//kill_processes(philo_mass, 1);
}

int init_threads(t_philo *philo_mass, t_input_data *input_data)
{
	pid_t ret;
	int i;

	i = 0;
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
		{
			check_num_of_eat(philo_mass);
		}
	}
	waitpid(-1, &g_status, 0);
	kill_processes(philo_mass, 0);
	return (0);
}

int start(char **argv, int flag, t_input_data *input_data)
{
	t_philo *philo_mass;
	pthread_t death_thread;

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
	philo_mass = (t_philo *)malloc(sizeof(t_philo) * input_data->ph_count);
	fill_mass_of_philo(philo_mass, input_data);
	if ((init_threads(philo_mass, input_data, death_thread))  == -1)
	{
		write(1, "thread error\n", 13);
		return (-1);
	}
	return (0);
}