/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:16:32 by welease           #+#    #+#             */
/*   Updated: 2021/01/04 22:23:12 by welease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*kill_all(t_philo *mass)
{
	int		i;
	int		ph_c;

	i = 0;
	ph_c = mass[0].input_data->ph_count;
	while (i < ph_c)
	{
		free(mass[i].input_data);
		pthread_mutex_destroy(&(g_forks_mass[i++]));
		pthread_mutex_destroy(&(mass[i].life_check_mutex));
	}
	free(g_forks_mass);
	free(mass);
	pthread_mutex_destroy(&g_print_mutex);
	pthread_mutex_destroy(&g_lifecheck_mutex);
	pthread_mutex_destroy(&g_tmp_mutex);
	return (NULL);
}

int			check_all_eating(t_philo *mass)
{
	int		ret;
	int		i;

	i = 0;
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

void		*check_deading(t_philo *mass)
{
	int		i;
	time_t	tmp;

	tmp = mass[0].input_data->t_to_die;
	while (!g_start_flag)
		;
	while (1)
	{
		i = -1;
		while (++i < mass[0].input_data->ph_count)
		{
			pthread_mutex_lock(&(mass[i].life_check_mutex));
			if (check_all_eating(mass))
				return (kill_all(mass));
			if (get_time() / 1000 - mass[i].eat_time > tmp)
			{
				philo_death(mass + i);
				return (kill_all(mass));
			}
			pthread_mutex_unlock(&(mass[i].life_check_mutex));
		}
		my_usleep(1000);
	}
	return (NULL);
}

int			init_threads(t_philo *philo_mass, t_input_data *input_data,
											pthread_t death_thread)
{
	int		i;

	i = 0;
	while (i < input_data->ph_count)
	{
		if (pthread_create(&((philo_mass[i]).philo_thread), NULL,
			(void *(*)(void *))simulation_start, ((void *)(philo_mass + i))))
			return (-1);
		i++;
	}
	if (pthread_create(&death_thread, NULL,
			(void *(*)(void *))check_deading, ((void *)(philo_mass))))
		return (-1);
	g_start_flag = 1;
	pthread_join(death_thread, NULL);
	return (0);
}

int			start(char **argv, int flag, t_input_data *input_data)
{
	t_philo		*philo_mass;
	pthread_t	death_thread;

	death_thread = NULL;
	if (pars_argv(argv, flag, input_data) == -1)
		return (-1);
	if (!(g_forks_mass = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
			input_data->ph_count)))
	{
		write(1, "mutex error\n", 12);
		return (-1);
	}
	forks_mass_init(input_data);
	if (!(philo_mass = (t_philo *)malloc(sizeof(t_philo) *
			input_data->ph_count)))
		return (-1);
	fill_mass_of_philo(philo_mass, input_data);
	if ((init_threads(philo_mass, input_data, death_thread)) == -1)
	{
		write(1, "thread error\n", 13);
		return (-1);
	}
	return (0);
}
