#include "philosophers.h"

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
	char *sem_name;
	char *sem_name1;
	int fork_index;
	int i;

	i = 0;
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